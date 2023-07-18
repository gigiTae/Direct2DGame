#include "RendererPCH.h"
#include "D2DRenderer.h"
#include "macro.h"
#include "D2DTexture.h"
#include "D2DCamera.h"

D2DRenderer::D2DRenderer()
	:m_hwnd(nullptr)
	,m_factory(nullptr)
	,m_IsD2DResReady(S_FALSE)
	,m_renderTargetSize{}
	,m_tempBrush(nullptr)
	,m_screenMatrix{}
	,m_camera(nullptr)
	,m_writeFactory(nullptr)
	,m_textFormat(nullptr)
	,m_imagingFactorty(nullptr)
	,m_finalMatrix{}
	,m_cameraAffected(true)
	,m_device(nullptr)
	,m_deviceContext(nullptr)
	,m_dpi(0.f)
	,m_targetBitmap(nullptr)
	,m_featureLevel{}
	,m_swapChain(nullptr)
	,m_d2dEffect{}
{
}

D2DRenderer::~D2DRenderer()
{
}


void D2DRenderer::Initalize(HWND _hwnd)
{
	HRESULT _hResult = CoInitialize(NULL);

	// 메인 윈도우 핸들 연결
	m_hwnd = _hwnd;

	HRESULT hr = S_OK;

	// Direct2D 리소스를 만드는데 사용할 수 있는 팩터리 개체생성
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED
		, &m_factory);
	assert(hr == S_OK);

	/// WIC팩토리 생성
	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			reinterpret_cast<void**>(&m_imagingFactorty)
		);
	}

	// 쓰기전용 팩토리 생성
	if (SUCCEEDED(hr))
	{
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED
			, __uuidof(m_writeFactory)
			, reinterpret_cast<IUnknown**>(&m_writeFactory)
		);
	}

	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = m_writeFactory->CreateTextFormat(
			L"굴림",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			15,
			L"", //locale
			&m_textFormat
		);
	}

	// 텍스트 정렬 방식
	if (SUCCEEDED(hr))
	{
		// Left-Top the text horizontally and vertically.
		m_textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		m_textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	}

	hr = CreateDeviceResources();
	assert(hr == S_OK);


	m_renderTargetSize = m_deviceContext->GetSize();

	/// 원점을 윈도우 중앙좌표로 이동하는 행렬
	Vector2 translation{m_renderTargetSize.width * 0.5f, m_renderTargetSize.height * 0.5f };
	Matrix3x2F transformMatrix = Matrix3x2F::Translation(translation.x, translation.y);

	/// 스크린 행렬 
	m_screenMatrix = transformMatrix;

	/// 카메라 생성
	m_camera = new D2DCamera();
	m_camera->ResetCamera(Vector2(m_renderTargetSize.width,m_renderTargetSize.height));

	// 이펙트 생성
	CreateEffects();
}

void D2DRenderer::BeginRender()
{
	m_IsD2DResReady = CreateDeviceResources();

	// 디바이스 종속적 자원들이 문제 없고, 랜더링을 할 수 있는 상황일 때 
	if(SUCCEEDED(m_IsD2DResReady))
	{
		m_renderTargetSize = m_deviceContext->GetSize();

		m_deviceContext->BeginDraw();

		/// 최종 행렬 계산
		D2D1_MATRIX_3X2_F cameraMatix = m_camera->GetCameraMatrix();
		m_finalMatrix = cameraMatix * m_screenMatrix;

		m_deviceContext->SetTransform(m_finalMatrix);

		m_deviceContext->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	}
}

void D2DRenderer::EndRender()
{
	if (SUCCEEDED(m_IsD2DResReady))
	{
		HRESULT hr = m_deviceContext->EndDraw();

		DXGI_PRESENT_PARAMETERS parameters{};
		parameters.DirtyRectsCount = 0;
		parameters.pDirtyRects = nullptr;
		parameters.pScrollOffset = nullptr;
		parameters.pScrollRect = nullptr;

		m_swapChain->Present1(1, 0, &parameters);


		//복구할 수 있는 프레젠테이션 오류가 있습니다. 호출자는 다시 만들고
		//전체 프레임을 다시 렌더링하고, 현재를 다시 시도해야 합니다.
		if (hr == D2DERR_RECREATE_TARGET)
		{
			hr = S_OK;
			DiscardDeviceResources();
		}
	}
}


void D2DRenderer::SetCameraAffected(bool _isAffected)
{
	if (m_cameraAffected != _isAffected)
	{
		m_cameraAffected = _isAffected;

		// 카메라에 영향을 받는 경우
		if (m_cameraAffected)
		{
			m_finalMatrix = m_camera->GetCameraMatrix() * m_screenMatrix;
		}
		else // 받지 않는 경우
		{
			m_finalMatrix = m_screenMatrix;
		}

		SetTransform();
	}
}

void D2DRenderer::Finalize()
{
	/// 리소스 메모리 해제
	for (auto iter = m_textures.begin(); iter != m_textures.end(); ++iter)
	{
		if (iter->second != nullptr)
		{
			delete iter->second;
		}
	}

	SafeRelease(&m_writeFactory);
	SafeRelease(&m_textFormat);
	SafeRelease(&m_imagingFactorty);
	SafeRelease(&m_deviceContext);
	SafeRelease(&m_factory);
	
	// 카메라 해제
	if (m_camera != nullptr)
		delete m_camera;

	//현재 스레드에서 COM 라이브러리를 닫고, 스레드에 의해 로드된 모든 DLL을 언로드하고
	//, 스레드가 유지 관리하는 다른 모든 리소스를 해제하고, 스레드의 모든 RPC 연결을 강제로 닫습니다.
	CoUninitialize();
}

void D2DRenderer::SetTransform(float _radian, Vector2 _point)
{
	/// radian이 증가할수록 반시계방향으로 회전한다
	float angle = -FMath::RadToDeg(_radian);

	// 행렬변환
	D2D1_MATRIX_3X2_F matrix = D2D1::Matrix3x2F::Rotation(angle, _point.ToPoint2F());
	
	matrix = matrix * m_finalMatrix;

	m_deviceContext->SetTransform(matrix);
}



void D2DRenderer::DrawLine(Vector2 _point1, Vector2 _point2, ColorF color)
{
	Vector2 point1 = _point1.ChangeYSign();
	Vector2 point2 = _point2.ChangeYSign();

	D2D1_POINT_2F start = point1.ToPoint2F();
	D2D1_POINT_2F end = point2.ToPoint2F();

	m_deviceContext->CreateSolidColorBrush(color, &m_tempBrush);
	assert(m_tempBrush);

	m_deviceContext->DrawLine(start, end, m_tempBrush, 1.0f);

	SafeRelease(&m_tempBrush);
}

void D2DRenderer::DrawEllipse(Vector2 _point , Vector2 _scale, COLORREF color)
{
	Vector2 point = _point.ChangeYSign();

	D2D1_ELLIPSE region{};
	region.point = point.ToPoint2F();
	region.radiusX = _scale.x * 0.5f;
	region.radiusY = _scale.y * 0.5f;

	m_deviceContext->CreateSolidColorBrush(D2D1::ColorF(color), &m_tempBrush);
	assert(m_tempBrush);

	m_deviceContext->DrawEllipse(region, m_tempBrush,1.f);

	SafeRelease(&m_tempBrush);
}

void D2DRenderer::DrawEllipse(Vector2 _point, float _radius, COLORREF color)
{
	Vector2 point = _point.ChangeYSign();

	D2D1_ELLIPSE region{};
	region.point = point.ToPoint2F();
	region.radiusX = _radius;
	region.radiusY = _radius;

	m_deviceContext->CreateSolidColorBrush(D2D1::ColorF(color), &m_tempBrush);
	assert(m_tempBrush);

	m_deviceContext->DrawEllipse(region, m_tempBrush, 2.f);

	SafeRelease(&m_tempBrush);
}

void D2DRenderer::DrawRectangle(Vector2 _leftTop
	, Vector2 _rightBottom, ColorF color,float _rotation)
{
	Vector2 leftTop = _leftTop.ChangeYSign();
	Vector2 rightBottom = _rightBottom.ChangeYSign();

	D2D1_RECT_F rt{};
	rt.left = leftTop.x;
	rt.top = leftTop.y;
	rt.right = rightBottom.x;
	rt.bottom = rightBottom.y;	

	m_deviceContext->CreateSolidColorBrush(color, &m_tempBrush);
	assert(m_tempBrush);

	Vector2 middle((rightBottom.x + leftTop.x) * 0.5f, (leftTop.y + rightBottom.y) * 0.5f);
	SetTransform(_rotation, middle);

	m_deviceContext->DrawRectangle(rt, m_tempBrush, 2.f);

	SetTransform();

	SafeRelease(&m_tempBrush);
}


void D2DRenderer::DrawFillRectangle(Vector2 _position, Vector2 _scale, ColorF color /*= D2D1::ColorF(ColorF::White,1.f)*/, float _rotation /*= 0.f*/)
{
	Vector2 position = _position.ChangeYSign();

	D2D1_RECT_F rt{};
	rt.left = position.x - _scale.x * 0.5f;
	rt.top = position.y - _scale.y * 0.5f;
	rt.right = position.x + _scale.x * 0.5f;
	rt.bottom = position.y + _scale.y * 0.5f;

	m_deviceContext->CreateSolidColorBrush(color, &m_tempBrush);
	assert(m_tempBrush);

	SetTransform(_rotation, position);

	m_deviceContext->FillRectangle(rt, m_tempBrush);

	SetTransform(); 

	SafeRelease(&m_tempBrush);
}

void D2DRenderer::DrawFillRectangle2(Vector2 _leftTop, Vector2 _rightBottom, ColorF color /*= ColorF(ColorF::WhiteSmoke)*/, float _rotation /*= 0.f*/)
{
	Vector2 leftTop = _leftTop.ChangeYSign();
	Vector2 rightBottom = _rightBottom.ChangeYSign();

	D2D1_RECT_F rt{};
	rt.left = leftTop.x;
	rt.top = leftTop.y;
	rt.right = rightBottom.x;
	rt.bottom = rightBottom.y;

	m_deviceContext->CreateSolidColorBrush(color, &m_tempBrush);
	assert(m_tempBrush);

	Vector2 middle((rightBottom.x + leftTop.x) * 0.5f, (leftTop.y + rightBottom.y) * 0.5f);
	SetTransform(_rotation, middle);

	m_deviceContext->FillRectangle(rt, m_tempBrush);

	SetTransform();

	SafeRelease(&m_tempBrush);
}

void D2DRenderer::DrawTextW(const std::wstring& _str, Vector2 _leftTop, Vector2 _rightBottom
	, ColorF _color /*= D2D1::ColorF::White*/)
{
	Vector2 leftTop = _leftTop.ChangeYSign();
	Vector2 rightBottom = _rightBottom.ChangeYSign();

	// 글자 출력범위
	D2D1_RECT_F rect = D2D1::RectF(leftTop.x, leftTop.y, rightBottom.x, rightBottom.y);

	// 브러쉬 생성
	m_deviceContext->CreateSolidColorBrush(D2D1::ColorF(_color), &m_tempBrush);
	assert(m_tempBrush);
	m_deviceContext->DrawTextW(_str.c_str(), static_cast<UINT32>(_str.length())
		, m_textFormat, rect, m_tempBrush);

}

D2DTexture* D2DRenderer::LoadBitMap(const wstring& _key, const wchar_t* _filePath)
{
	HRESULT hr = S_OK;

	// 이미 만들어둔 텍스처이면 로드하지 않는다.
	auto iter = m_textures.find(_key);
	if (iter != m_textures.end())
	{
		return iter->second;
	}

	ID2D1Bitmap* bitmap = nullptr;

	hr = LoadBitmapFromFile(_filePath, 0, 0, &bitmap);

	assert(bitmap || !L"비트맵 불러오기에 실패하였습니다");

	/// 비트맵 로드에 성공
	if (!SUCCEEDED(hr))
	{
		return nullptr;
	}

	/// D2D 텍스처 생성
	D2DTexture* texture = new D2DTexture();
	texture->SetBitMap(bitmap);
	texture->SetFilePath(_filePath);
	texture->SetKey(_key);

	m_textures.insert(std::make_pair(_key, texture));

	return texture;
}

void D2DRenderer::DrawBitMap(const wstring& _key, Vector2 _position
	, float _rotation /*= 0.f*/, float _alpha /*= 1.f*/)
{
	auto iter = m_textures.find(_key);

	assert(iter != m_textures.end() || !L"텍스처 파일이 로드되지 않았습니다");

	D2DTexture* texture = iter->second;
	Vector2 position = _position.ChangeYSign();
	Vector2 halfSize = texture->GetSize() * 0.5f;

	D2D1_RECT_F rect{};
	rect.left = position.x - halfSize.x;
	rect.right = position.x + halfSize.x;
	rect.top = position.y + halfSize.y;
	rect.bottom = position.y - halfSize.y;

	if (_rotation != 0.f)
		SetTransform(_rotation, position);

	m_deviceContext->DrawBitmap(texture->GetBitmap(), rect
		, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, nullptr);

	m_d2dEffect[0]->SetInput(0, texture->GetBitmap(),false);
	m_deviceContext->DrawImage(m_d2dEffect[0], Point2F(rect.left,rect.bottom));

	if (_rotation != 0.f)
		SetTransform();
}

void D2DRenderer::DrawBitMap(const wstring& _key, Vector2 _position
	, Vector2 _textureLeftTop, Vector2 _sliceSize
	, float _rotation /*= 0.f*/, float _alpha /*= 1.f*/)
{
	// texture 불러오기 
	auto iter = m_textures.find(_key);
	assert(iter != m_textures.end() || !L"텍스처 파일이 로드되지 않았습니다");
	D2DTexture* texture = iter->second;

	// 스크린 좌표계로 변환 
	Vector2 position = _position.ChangeYSign();
	Vector2 halfSize = _sliceSize * 0.5f;

	// 화면에 출력하는 용도
	D2D1_RECT_F screen{};
	screen.left = position.x - halfSize.x;
	screen.right = position.x + halfSize.x;
	screen.top = position.y + halfSize.y;
	screen.bottom = position.y - halfSize.y;

	// 비트맵을 자르는 용도
	D2D1_RECT_F textureRect{};
	textureRect.left = _textureLeftTop.x;
	textureRect.top = _textureLeftTop.y;
	textureRect.right = _textureLeftTop.x + _sliceSize.x;
	textureRect.bottom = _textureLeftTop.y + _sliceSize.y;

	if (_rotation != 0.f)
		SetTransform(_rotation, position);

	m_deviceContext->DrawBitmap(texture->GetBitmap(), screen
		, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, textureRect);

	if (_rotation != 0.f)
		SetTransform();
}

HRESULT D2DRenderer::LoadBitmapFromFile(PCWSTR _filePath
	, UINT _destinationWidth, UINT _destinationHeight, ID2D1Bitmap** _bitmap)
{
	HRESULT hr = S_OK;

	IWICBitmapDecoder* decoder = NULL;
	IWICBitmapFrameDecode* source = NULL;
	IWICStream* stream = NULL;
	IWICFormatConverter* converter = NULL;
	IWICBitmapScaler* scaler = NULL;

	assert(m_imagingFactorty);

	hr = m_imagingFactorty->CreateDecoderFromFilename(
		_filePath, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);

	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = decoder->GetFrame(0, &source);
	}

	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = m_imagingFactorty->CreateFormatConverter(&converter);
	}

	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		if (_destinationWidth != 0 || _destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = source->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (_destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(_destinationHeight) / static_cast<FLOAT>(originalHeight);
					_destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (_destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(_destinationWidth) / static_cast<FLOAT>(originalWidth);
					_destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = m_imagingFactorty->CreateBitmapScaler(&scaler);
				if (SUCCEEDED(hr))
				{
					hr = scaler->Initialize(
						source,
						_destinationWidth,
						_destinationHeight,
						WICBitmapInterpolationModeCubic
					);
				}
				if (SUCCEEDED(hr))
				{
					hr = converter->Initialize(
						scaler,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
					);
				}
			}
		}
		else // Don't scale the image.
		{
			hr = converter->Initialize(
				source,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = m_deviceContext->CreateBitmapFromWicBitmap(
			converter,
			NULL,
			_bitmap
		);
	}

	SafeRelease(&decoder);
	SafeRelease(&source);
	SafeRelease(&stream);
	SafeRelease(&converter);
	SafeRelease(&scaler);

	return hr;
}

void D2DRenderer::CreateEffects()
{
	// 가우시안 블러 이펙트 테스트
	m_deviceContext->CreateEffect(CLSID_D2D1GaussianBlur, &m_d2dEffect[0]);
	m_d2dEffect[0]->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, 100.f);
	m_d2dEffect[0]->SetValue(D2D1_BORDER_MODE_HARD, 1);

	// 크로마키 이펙트 테스트.
	m_deviceContext->CreateEffect(CLSID_D2D1ChromaKey, &m_d2dEffect[1]);
	m_d2dEffect[1]->SetValue(D2D1_CHROMAKEY_PROP_COLOR, D2D1::Vector3F(1.0f, 0.0f, 1.0f)); // 크로마키로 제거하려는 생삭을 지정
	m_d2dEffect[1]->SetValue(D2D1_CHROMAKEY_PROP_TOLERANCE, 0.2f); //색상 제거의 허용 범위를 지정한다.
	m_d2dEffect[1]->SetValue(D2D1_CHROMAKEY_PROP_INVERT_ALPHA, false);
	m_d2dEffect[1]->SetValue(D2D1_CHROMAKEY_PROP_FEATHER, false);
}

HRESULT D2DRenderer::CreateDeviceResources()
{
	
	HRESULT hr = S_OK;

	if (m_deviceContext == nullptr)
	{
		// This flag adds support for surfaces with a different color channel ordering than the API default.
		// You need it for compatibility with Direct2D.
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

		// This array defines the set of DirectX hardware feature levels this app  supports.
		// The ordering is important and you should  preserve it.
		// Don't forget to declare your app's minimum required feature level in its
		// description.  All apps are assumed to support 9.1 unless otherwise stated.
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		// Create the DX11 API device object, and get a corresponding context.
		ID3D11Device* _D3D11Device;
		ID3D11DeviceContext* _D3D11DeviceContext;		// DirectX Core Objects. Required for 2D and 3D.

		D3D11CreateDevice(
			nullptr,                    // specify null to use the default adapter
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			creationFlags,              // optionally set debug and Direct2D compatibility flags
			featureLevels,              // list of feature levels this app can support
			ARRAYSIZE(featureLevels),   // number of possible feature levels
			D3D11_SDK_VERSION,
			&_D3D11Device,              // returns the Direct3D device created
			&m_featureLevel,            // returns feature level of device created
			&_D3D11DeviceContext		// returns the device immediate context
		);

		assert(_D3D11Device);

		// Obtain the underlying DXGI device of the Direct3D11 device.
		IDXGIDevice* dxgiDevice;
		_D3D11Device->QueryInterface(&dxgiDevice);	/// ComPtr.As()
		assert(dxgiDevice);

		// Obtain the Direct2D device for 2-D rendering.
		m_factory->CreateDevice(dxgiDevice, &m_device);

		// Get Direct2D device's corresponding device context object.
		hr = m_device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
			&m_deviceContext);

		//if (SUCCEEDED(hr))
		//{
		//	// Create brushes.
		//	hr = m_deviceContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pWhiteBrush);
		//	hr = m_deviceContext->CreateSolidColorBrush(ColorF(1.0f, 1.0f, 0.f), &m_pYellowBrush);
		//	hr = m_deviceContext->CreateSolidColorBrush(ColorF(1.0f, 1.0f, 1.0f), &m_pNowBrush);
		//}

		// Allocate a descriptor.
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
		swapChainDesc.Width = 0;                           // 0 : use automatic sizing
		swapChainDesc.Height = 0;
		swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // this is the most common swapchain format
		swapChainDesc.Stereo = false;
		swapChainDesc.SampleDesc.Count = 1;                // don't use multi-sampling
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;                     // use double buffering to enable flip
		swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; // all apps must use this SwapEffect
		swapChainDesc.Flags = 0;

		// Identify the physical adapter (GPU or card) this device is runs on.
		IDXGIAdapter* dxgiAdapter;
		dxgiDevice->GetAdapter(&dxgiAdapter);

		// Get the factory object that created the DXGI device.
		IDXGIFactory2* dxgiFactory;
		dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

		// Get the final swap chain for this window from the DXGI factory.
		DXGI_RATIONAL rate{};
		rate.Denominator = 60;
		rate.Numerator = 1;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainDescFull{};
		swapChainDescFull.RefreshRate = rate;
		swapChainDescFull.Scaling = DXGI_MODE_SCALING_STRETCHED;
		swapChainDescFull.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST;
		swapChainDescFull.Windowed = true;

		dxgiFactory->CreateSwapChainForHwnd(_D3D11Device,
			m_hwnd,
			&swapChainDesc,
			&swapChainDescFull, // 전체화면 스왑체인 설정
			nullptr,
			&m_swapChain);

		// Ensure that DXGI doesn't queue more than one frame at a time.
		///dxgiDevice->SetMaximumFrameLatency(1);

		// Get the backbuffer for this window which is be the final 3D render target.
		ID3D11Texture2D* _backBuffer;
		m_swapChain->GetBuffer(0, IID_PPV_ARGS(&_backBuffer));

		// Now we set up the Direct2D render target bitmap linked to the swapchain. 
		// Whenever we render to this bitmap, it is directly rendered to the 
		// swap chain associated with the window.
		D2D1_BITMAP_PROPERTIES1 _bitmapProperties =
			BitmapProperties1(
				D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
				PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
				m_dpi,
				m_dpi
			);

		// Direct2D needs the dxgi version of the backbuffer surface pointer.
		IDXGISurface* dxgiBackBuffer;
		m_swapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer));
		assert(dxgiBackBuffer);

		// Get a D2D surface from the DXGI back buffer to use as the D2D render target.
		m_deviceContext->CreateBitmapFromDxgiSurface(
			dxgiBackBuffer,
			&_bitmapProperties,
			&m_targetBitmap
		);

		// Now we can set the Direct2D render target.
		m_deviceContext->SetTarget(m_targetBitmap);
	}

	return hr;
}

void D2DRenderer::DiscardDeviceResources()
{
	SafeRelease(&m_deviceContext);
}
