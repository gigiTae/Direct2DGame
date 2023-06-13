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
	/// �׸��� ���� �Լ���
	
	// ������ �׸��� �Լ�
	void DrawLine(Vector2 _point1, Vector2 _point2
		, COLORREF color =RGB(255, 255, 255));

	void DrawEllipse(Vector2 _point, Vector2 _radius
		, COLORREF color = RGB(255, 255, 255) );

	void DrawEllipse(Vector2 _point, float _radius,
		COLORREF color = RGB(255, 255, 255));

	// �簢�� �׸��� �Լ�
	void DrawRectangle(Vector2 _leftTop, Vector2 _rightBottom
		, COLORREF color = RGB(255, 255, 255), float _rotation = 0.f);

private:
	// ����Ÿ���� ����� �Լ�
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();

private: 
	// ���� ������ �ڵ�
	HWND m_hwnd;
	ID2D1Factory* m_direct2DFactory;
	ID2D1HwndRenderTarget* m_renderTarget;
	
	// ���� ���� 
	IDWriteFactory* m_writeFactory;
	IDWriteTextFormat* m_textFormat;

	// �귯��
	ID2D1SolidColorBrush* m_nowBrush; // �ٲ㰡�鼭 ����ϴ� �뵵
	ID2D1SolidColorBrush* m_tempBrush; // ��� ����ϴ� �뵵

private:
	// ����̽� �������� �ڿ����� �غ�Ǿ��°�?
	HRESULT m_IsD2DResReady;
	D2D1_SIZE_F m_renderTargetSize;
};

