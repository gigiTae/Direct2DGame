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
	
	
	void SetTransform(float _radian, Vector2 _point);

public:
	/// 그리기 관련 함수들
	
	// 직선을 그리는 함수
	void DrawLine(Vector2 _point1, Vector2 _point2
		, COLORREF color =RGB(255, 255, 255));

	void DrawEllipse(Vector2 _point, Vector2 _radius
		, COLORREF color = RGB(255, 255, 255) );

	void DrawEllipse(Vector2 _point, float _radius,
		COLORREF color = RGB(255, 255, 255));

	// 사각형 그리는 함수
	void DrawRectangle(Vector2 _leftTop, Vector2 _rightBottom
		, COLORREF color = RGB(255, 255, 255), float _rotation = 0.f);

private:
	// 랜더타겟을 만드는 함수
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();

private: 
	// 메인 윈도우 핸들
	HWND m_hwnd;
	ID2D1Factory* m_direct2DFactory;
	ID2D1HwndRenderTarget* m_renderTarget;
	
	// 쓰기 전용 
	IDWriteFactory* m_writeFactory;
	IDWriteTextFormat* m_textFormat;

	// 브러쉬
	ID2D1SolidColorBrush* m_nowBrush; // 바꿔가면서 사용하는 용도
	ID2D1SolidColorBrush* m_tempBrush; // 잠시 사용하는 용도

private:
	// 디바이스 종속적인 자원들이 준비되었는가?
	HRESULT m_IsD2DResReady;
	D2D1_SIZE_F m_renderTargetSize;
};

