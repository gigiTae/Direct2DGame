
#include "RendererPCH.h"
#include "D2DRenderer.h"

D2DRenderer::D2DRenderer()
	:m_hwnd(nullptr)
	,m_direct2DFactory(nullptr)
	,m_renderTarget(nullptr)
	,m_IsD2DResReady(S_FALSE)
	,m_renderTargetSize{}
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

		if (hr == D2DERR_RECREATE_TARGET)
		{
			hr = S_OK;
			//DiscardDeviceResources();
			
		}


	}
}

void D2DRenderer::Finalize()
{
}

void D2DRenderer::DrawLine(Vector2 _start, Vector2 _end, COLORREF color)
{
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
