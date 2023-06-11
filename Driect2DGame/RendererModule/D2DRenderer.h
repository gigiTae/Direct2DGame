#pragma once

struct Vector2;

class D2DRenderer
{
public:
	D2DRenderer();
	~D2DRenderer();

	void Initalize(HWND _hwnd);
	void BeginRender();
	void EndRender();
	
	void Finalize();

	
public:
	// 그리기 함수들 추가
	void DrawLine(Vector2 _start, Vector2 _end, COLORREF color = COLORREF(RGB(0, 0, 0)));

private:
	// 랜더타겟을 만드는 함수
	HRESULT CreateDeviceResources();

private: 
	// 메인 윈도우 핸들
	HWND m_hwnd;
	ID2D1Factory* m_direct2DFactory;
	ID2D1HwndRenderTarget* m_renderTarget;
	
	IDWriteFactory* m_writeFactory;
	IDWriteTextFormat* m_textFormat;

private:
	// 디바이스 종속적인 자원들이 준비되었는가?
	HRESULT m_IsD2DResReady;
	D2D1_SIZE_F m_renderTargetSize;

};

