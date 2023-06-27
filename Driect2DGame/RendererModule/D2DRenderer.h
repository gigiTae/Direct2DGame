#pragma once

/// <summary>
/// D2D�������� ����Ѵ�
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
	/// �׸��� ���� �Լ���
	void DrawBitMap();
	// ������ �׸��� �Լ�
	void DrawLine(Vector2 _point1, Vector2 _point2
		, COLORREF = D2D1::ColorF::White);

	void DrawEllipse(Vector2 _point, Vector2 _radius
		, COLORREF = D2D1::ColorF::White);

	void DrawEllipse(Vector2 _point, float _radius,
		COLORREF color = D2D1::ColorF::White);

	// �簢�� �׸��� �Լ�
	void DrawRectangle(Vector2 _leftTop, Vector2 _rightBottom
		, COLORREF color = D2D1::ColorF::White, float _rotation = 0.f);

	/// ���� ���� �Լ�
	void DrawTextW(const std::wstring& _str, Vector2 _leftTop, Vector2 _rightBottom, COLORREF _color = D2D1::ColorF::White);

	// ��Ʈ�� �ε�
	void LoadBitMap(const wchar_t* _filePath, ID2D1Bitmap* _bitmap);

private:
	// ����Ÿ���� ����� �Լ�
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();

	//HRESULT LoadBitmapFromFile()

private: 
	// ���� ������ �ڵ�
	HWND m_hwnd;
	ID2D1Factory* m_factory;
	ID2D1HwndRenderTarget* m_renderTarget;
	
	// ��Ʈ��


	// ���� ���� 
	IDWriteFactory* m_writeFactory;
	IDWriteTextFormat* m_textFormat;

	// �귯
	ID2D1SolidColorBrush* m_tempBrush; // ��� ����ϴ� �뵵

private:
	// ����̽� �������� �ڿ����� �غ�Ǿ��°�?
	HRESULT m_IsD2DResReady;
	D2D1_SIZE_F m_renderTargetSize;
};

