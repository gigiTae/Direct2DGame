#include "RendererPCH.h"
#include "D2DRenderer.h"
#include "macro.h"
#include "D2DTexture.h"

D2DRenderer::D2DRenderer()
	:m_hwnd(nullptr)
	,m_factory(nullptr)
	,m_renderTarget(nullptr)
	,m_IsD2DResReady(S_FALSE)
	,m_renderTargetSize{}
	,m_tempBrush(nullptr)
	,m_screenTrasformMatrix{}
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

	hr = CreateDeviceResources();
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
			10,
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

	m_renderTargetSize = m_renderTarget->GetSize();

	/// 원점을 윈도우 중앙좌표로 이동하는 행렬
	Vector2 translation{m_renderTargetSize.width * 0.5f, m_renderTargetSize.height * 0.5f };

	Matrix3x2F transformMatrix = Matrix3x2F::Translation(translation.x, translation.y);

	/// 최종 변환 행렬 

	m_screenTrasformMatrix = transformMatrix;
}

void D2DRenderer::BeginRender()
{
	m_IsD2DResReady = CreateDeviceResources();

	// 디바이스 종속적 자원들이 문제 없고, 랜더링을 할 수 있는 상황일 때 
	if(SUCCEEDED(m_IsD2DResReady) &&
		!(m_renderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		m_renderTargetSize = m_renderTarget->GetSize();

		m_renderTarget->BeginDraw();

		m_renderTarget->SetTransform(m_screenTrasformMatrix);

		m_renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	}


}

void D2DRenderer::EndRender()
{
	if (SUCCEEDED(m_IsD2DResReady) &&
		!(m_renderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		HRESULT hr = m_renderTarget->EndDraw();

		//복구할 수 있는 프레젠테이션 오류가 있습니다. 호출자는 다시 만들고
		//전체 프레임을 다시 렌더링하고, 현재를 다시 시도해야 합니다.
		if (hr == D2DERR_RECREATE_TARGET)
		{
			hr = S_OK;
			DiscardDeviceResources();
		}
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
	SafeRelease(&m_renderTarget);
	SafeRelease(&m_factory);
	

	//현재 스레드에서 COM 라이브러리를 닫고, 스레드에 의해 로드된 모든 DLL을 언로드하고
	//, 스레드가 유지 관리하는 다른 모든 리소스를 해제하고, 스레드의 모든 RPC 연결을 강제로 닫습니다.
	CoUninitialize();
}

void D2DRenderer::SetTransform(float _radian, Vector2 _point)
{
	/// radian이 증가할수록 반시계방향으로 회전한다
	float angle = -FMath::Rad2Deg(_radian);

	// 행렬변환
	D2D1_MATRIX_3X2_F matrix = D2D1::Matrix3x2F::Rotation(angle, _point.ToPoint2F());
	
	matrix = matrix * m_screenTrasformMatrix;

	m_renderTarget->SetTransform(matrix);
}


void D2DRenderer::DrawLine(Vector2 _point1, Vector2 _point2, COLORREF color)
{
	Vector2 point1 = _point1.ToScreenPoint();
	Vector2 point2 = _point2.ToScreenPoint();

	D2D1_POINT_2F start = point1.ToPoint2F();
	D2D1_POINT_2F end = point2.ToPoint2F();

	m_renderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &m_tempBrush);
	assert(m_tempBrush);

	m_renderTarget->DrawLine(start, end, m_tempBrush, 1.0f);

	SafeRelease(&m_tempBrush);
}

void D2DRenderer::DrawEllipse(Vector2 _point , Vector2 _scale, COLORREF color)
{
	Vector2 point = _point.ToScreenPoint();

	D2D1_ELLIPSE region{};
	region.point = point.ToPoint2F();
	region.radiusX = _scale.x * 0.5f;
	region.radiusY = _scale.y * 0.5f;

	m_renderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &m_tempBrush);
	assert(m_tempBrush);

	m_renderTarget->DrawEllipse(region, m_tempBrush,2.f);

	SafeRelease(&m_tempBrush);
}

void D2DRenderer::DrawEllipse(Vector2 _point, float _radius, COLORREF color)
{
	Vector2 point = _point.ToScreenPoint();

	D2D1_ELLIPSE region{};
	region.point = point.ToPoint2F();
	region.radiusX = _radius;
	region.radiusY = _radius;

	m_renderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &m_tempBrush);
	assert(m_tempBrush);

	m_renderTarget->DrawEllipse(region, m_tempBrush, 2.f);

	SafeRelease(&m_tempBrush);
}

void D2DRenderer::DrawRectangle(Vector2 _leftTop, Vector2 _rightBottom, COLORREF color,float _rotation)
{
	Vector2 leftTop = _leftTop.ToScreenPoint();
	Vector2 rightBottom = _rightBottom.ToScreenPoint();

	D2D1_RECT_F rt{};
	rt.left = leftTop.x;
	rt.top = leftTop.y;
	rt.right = rightBottom.x;
	rt.bottom = rightBottom.y;
	 
	m_renderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &m_tempBrush);
	assert(m_tempBrush);

	Vector2 middle((rightBottom.x + leftTop.x) * 0.5f, (leftTop.y + rightBottom.y) * 0.5f);
	SetTransform(_rotation, middle);

	m_renderTarget->DrawRectangle(rt, m_tempBrush, 2.f);

	SetTransform();

	SafeRelease(&m_tempBrush);
}

void D2DRenderer::DrawTextW(const std::wstring& _str, Vector2 _leftTop, Vector2 _rightBottom
	, COLORREF _color /*= D2D1::ColorF::White*/)
{
	Vector2 leftTop = _leftTop.ToScreenPoint();
	Vector2 rightBottom = _rightBottom.ToScreenPoint();

	// 글자 출력범위
	D2D1_RECT_F rect = D2D1::RectF(leftTop.x, leftTop.y, rightBottom.x, rightBottom.y);

	// 브러쉬 생성
	m_renderTarget->CreateSolidColorBrush(D2D1::ColorF(_color), &m_tempBrush);
	assert(m_tempBrush);
	m_renderTarget->DrawTextW(_str.c_str(), static_cast<UINT32>(_str.length())
		, m_textFormat, rect, m_tempBrush);

}

D2DTexture* D2DRenderer::LoadBitMap(const wstring& _key, const wchar_t* _filePath)
{
	HRESULT hr = S_OK;

	auto iter = m_textures.find(_key);
	if (iter != m_textures.end())
	{
		return iter->second;
	}

	ID2D1Bitmap* bitmap = nullptr;

	hr = LoadBitmapFromFile(_filePath, 0, 0, &bitmap);

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
	Vector2 position = _position.ToScreenPoint();
	Vector2 halfSize = texture->GetSize() * 0.5f;

	D2D1_RECT_F rect{};
	rect.left = position.x - halfSize.x;
	rect.right = position.x + halfSize.x;
	rect.top = position.y + halfSize.y;
	rect.bottom = position.y - halfSize.y;

	if (_rotation != 0.f)
		SetTransform(_rotation, position);

	m_renderTarget->DrawBitmap(texture->GetBitmap(), rect
		, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, nullptr);

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
	Vector2 position = _position.ToScreenPoint();
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

	m_renderTarget->DrawBitmap(texture->GetBitmap(), screen
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
		hr = m_renderTarget->CreateBitmapFromWicBitmap(
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

HRESULT D2DRenderer::CreateDeviceResources()
{
	
	HRESULT hr = S_OK;
	if (m_renderTarget == nullptr)
	{
		RECT rc{};

		// 창 클라이언트 영역 좌표
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left
			, rc.bottom - rc.top);

		// 렌더 타겟생성
		hr = m_factory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties()
			, D2D1::HwndRenderTargetProperties(m_hwnd, size,D2D1_PRESENT_OPTIONS_IMMEDIATELY)
			, &m_renderTarget);
	}

	return hr;
}

void D2DRenderer::DiscardDeviceResources()
{
	SafeRelease(&m_renderTarget);
}
