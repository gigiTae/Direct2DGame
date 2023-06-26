#pragma once

/// <summary>
/// D2D랜더링을 담당한다
/// 
/// </summary>
class D2DRenderer
{
public:
	D2DRenderer();
	~D2DRenderer();

	void Initalize(HWND _hwnd);
	void BeginRender();
	void EndRender();
	
	void Finalize();
	void SetTransform(float _radian = 0.f, Vector2 _point = Vector2::Zero);

public:
	/// 그리기 관련 함수들
	void DrawBitMap();
	// 직선을 그리는 함수
	void DrawLine(Vector2 _point1, Vector2 _point2
		, COLORREF = D2D1::ColorF::White);

	void DrawEllipse(Vector2 _point, Vector2 _radius
		, COLORREF = D2D1::ColorF::White);

	void DrawEllipse(Vector2 _point, float _radius,
		COLORREF color = D2D1::ColorF::White);

	// 사각형 그리는 함수
	void DrawRectangle(Vector2 _leftTop, Vector2 _rightBottom
		, COLORREF color = D2D1::ColorF::White, float _rotation = 0.f);

	/// 쓰기 관련 함수
	void DrawTextW(const std::wstring& _str, Vector2 _leftTop, Vector2 _rightBottom, COLORREF _color = D2D1::ColorF::White);

	// 비트맵 로드
	void LoadBitMap(const wchar_t* _filePath, ID2D1Bitmap* _bitmap);

private:
	// 랜더타겟을 만드는 함수
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();

	//HRESULT LoadBitmapFromFile()

private: 
	// 메인 윈도우 핸들
	HWND m_hwnd;
	ID2D1Factory* m_factory;
	ID2D1HwndRenderTarget* m_renderTarget;
	
	// 비트맵


	// 쓰기 전용 
	IDWriteFactory* m_writeFactory;
	IDWriteTextFormat* m_textFormat;

	// 브러
	ID2D1SolidColorBrush* m_tempBrush; // 잠시 사용하는 용도

private:
	// 디바이스 종속적인 자원들이 준비되었는가?
	HRESULT m_IsD2DResReady;
	D2D1_SIZE_F m_renderTargetSize;
};

