
#include "MathModuleHeader.h"
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
	// ���� ������ �ڵ� ����
	m_hwnd = _hwnd;

	HRESULT hr = S_OK;

	// Direct2D ���ҽ��� ����µ� ����� �� �ִ� ���͸� ��ü����
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED
		, &m_direct2DFactory);
	assert(hr == S_OK);

	hr = CreateDeviceResources();
	assert(hr == S_OK);


}

void D2DRenderer::BeginRender()
{
	m_IsD2DResReady = CreateDeviceResources();

	// ����̽� ������ �ڿ����� ���� ����, �������� �� �� �ִ� ��Ȳ�� �� 
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

		//������ �� �ִ� ���������̼� ������ �ֽ��ϴ�. ȣ���ڴ� �ٽ� �����
		//��ü �������� �ٽ� �������ϰ�, ���縦 �ٽ� �õ��ؾ� �մϴ�.
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

	//���� �����忡�� COM ���̺귯���� �ݰ�, �����忡 ���� �ε�� ��� DLL�� ��ε��ϰ�
	//, �����尡 ���� �����ϴ� �ٸ� ��� ���ҽ��� �����ϰ�, �������� ��� RPC ������ ������ �ݽ��ϴ�.
	CoUninitialize();
}

void D2DRenderer::SetTransform(float _radian, Vector2 _point)
{
	Vector2 point = _point.ToScreenPoint(m_renderTargetSize);

	float angle = FMath::Rad2Deg(_radian);

	// ��ĺ�ȯ
	D2D1_MATRIX_3X2_F matrix = D2D1::Matrix3x2F::Rotation(angle, point.ToPoint2F());

	m_renderTarget->SetTransform(matrix);
}

void D2DRenderer::DrawLine(Vector2 _point1, Vector2 _point2, COLORREF color)
{
	// ��ũ�� ��ǥ��� ��ȯ
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
	// ��ũ�� ��ǥ��� ��ȯ
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
	// ��ũ�� ��ǥ��� ��ȯ
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
	// ��ũ�� ��ǥ��� ��ȯ
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

		// â Ŭ���̾�Ʈ ���� ��ǥ
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left
			, rc.bottom - rc.top);

		// ���� Ÿ�ٻ���
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
