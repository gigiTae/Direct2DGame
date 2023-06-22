
#include "RendererPCH.h"
#include "D2DRenderer.h"
#include "macro.h"

D2DRenderer::D2DRenderer()
	:m_hwnd(nullptr)
	,m_direct2DFactory(nullptr)
	,m_renderTarget(nullptr)
	,m_IsD2DResReady(S_FALSE)
	,m_renderTargetSize{}
	,m_nowBrush(nullptr)
	,m_tempBrush(nullptr)
{
}

D2DRenderer::~D2DRenderer()
{
}


void D2DRenderer::Initalize(HWND _hwnd)
{
	// 메인 윈도우 핸들 연결
	m_hwnd = _hwnd;

	HRESULT hr = S_OK;

	// Direct2D 리소스를 만드는데 사용할 수 있는 팩터리 개체생성
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED
		, &m_direct2DFactory);
	assert(hr == S_OK);

	hr = CreateDeviceResources();
	assert(hr == S_OK);

	if (SUCCEEDED(hr))
	{
		// 쓰기전용 팩토리 생성?
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

		m_renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		
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
	SafeRelease(&m_direct2DFactory);
	SafeRelease(&m_renderTarget);

	//현재 스레드에서 COM 라이브러리를 닫고, 스레드에 의해 로드된 모든 DLL을 언로드하고
	//, 스레드가 유지 관리하는 다른 모든 리소스를 해제하고, 스레드의 모든 RPC 연결을 강제로 닫습니다.
	CoUninitialize();
}

void D2DRenderer::SetTransform(float _radian, Vector2 _point)
{
	Vector2 point = _point.ToScreenPoint(m_renderTargetSize);

	float angle = FMath::Rad2Deg(_radian);

	// 행렬변환
	D2D1_MATRIX_3X2_F matrix = D2D1::Matrix3x2F::Rotation(angle, point.ToPoint2F());

	m_renderTarget->SetTransform(matrix);
}

void D2DRenderer::DrawBitMap()
{
	//m_renderTarget->DrawBitmap()

}

void D2DRenderer::DrawLine(Vector2 _point1, Vector2 _point2, COLORREF color)
{
	// 스크린 좌표계로 변환
	Vector2 point1 = _point1.ToScreenPoint(m_renderTargetSize);
	Vector2 point2 = _point2.ToScreenPoint(m_renderTargetSize);

	D2D1_POINT_2F start = point1.ToPoint2F();
	D2D1_POINT_2F end = point2.ToPoint2F();

	m_renderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &m_tempBrush);
	assert(m_tempBrush);

	m_renderTarget->DrawLine(start, end, m_tempBrush, 1.0f);

	SafeRelease(&m_tempBrush);
}

void D2DRenderer::DrawEllipse(Vector2 _point , Vector2 _scale, COLORREF color)
{
	// 스크린 좌표계로 변환
	Vector2 point = _point.ToScreenPoint(m_renderTargetSize);

	D2D1_ELLIPSE region;
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
	// 스크린 좌표계로 변환
	Vector2 point = _point.ToScreenPoint(m_renderTargetSize);

	D2D1_ELLIPSE region;
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
	// 스크린 좌표계로 변환
	Vector2 leftTop = _leftTop.ToScreenPoint(m_renderTargetSize);
	Vector2 rightBottom = _rightBottom.ToScreenPoint(m_renderTargetSize);

	D2D1_RECT_F rt;
	rt.left = leftTop.x;
	rt.top = leftTop.y;
	rt.right = rightBottom.x;
	rt.bottom = rightBottom.y;

	m_renderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &m_tempBrush);
	assert(m_tempBrush);

	m_renderTarget->DrawRectangle(rt, m_tempBrush, 2.f);

	SafeRelease(&m_tempBrush);
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
		hr = m_direct2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties()
			, D2D1::HwndRenderTargetProperties(m_hwnd, size)
			, &m_renderTarget);
	}

	return hr;
}

void D2DRenderer::DiscardDeviceResources()
{
	SafeRelease(&m_renderTarget);
}
