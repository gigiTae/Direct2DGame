#pragma once

class D2DTexture;
class D2DCamera;

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
	void Finalize();

	void BeginRender();
	void EndRender();

private:
	void SetTransform(float _radian, Vector2 _point);
	// �⺻ ��ķ� ��ȯ
	void SetTransform() { m_renderTarget->SetTransform(m_finalMatrix); }

public:
	/// �׸��� ���� �Լ���

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
	void DrawTextW(const std::wstring& _str, Vector2 _leftTop
		, Vector2 _rightBottom, COLORREF _color = D2D1::ColorF::White);

public:
	/// ��Ʈ�� �ε�
	D2DTexture* LoadBitMap(const wstring& _key, const wchar_t* _filePath);

	void DrawBitMap(const wstring& _key, Vector2 _position
		, float _rotation = 0.f, float _alpha = 1.f);

	// �ؽ�ó�� �߶� ������
	void DrawBitMap(const wstring& _key, Vector2 _position
		, Vector2 _textureLeftTop, Vector2 _sliceSize
		, float _rotation = 0.f, float _alpha = 1.f);
	
	/// ī�޶� ����
	D2DCamera* GetCamera()const { return m_camera; }

private:
	HRESULT LoadBitmapFromFile(PCWSTR _filePath
		, UINT _destinationWidth, UINT _destinationHeight, ID2D1Bitmap** _bitmap);

private:
	/// ����Ÿ���� ����� �Լ�
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();

	//HRESULT LoadBitmapFromFile()
private:
	D2D1_MATRIX_3X2_F m_screenMatrix; // ��ũ�� ��ǥ��� ��ȯ�ϴ� ���
	D2D1_MATRIX_3X2_F m_finalMatrix;

	// ���� ������ �ڵ�
	HWND m_hwnd;
	ID2D1Factory* m_factory;
	ID2D1HwndRenderTarget* m_renderTarget;
	
	// ���� ���� 
	IDWriteFactory* m_writeFactory;
	IDWriteTextFormat* m_textFormat;

	// �귯
	ID2D1SolidColorBrush* m_tempBrush; // ��� ����ϴ� �뵵

private:
	// ����̽� �������� �ڿ����� �غ�Ǿ��°�?
	HRESULT m_IsD2DResReady;
	D2D1_SIZE_F m_renderTargetSize;

private:
	/// ��Ʈ�� ���� 
	IWICImagingFactory* m_imagingFactorty;

	/// �ؽ�ó�� �����ϴ� ����
	map<wstring, D2DTexture*> m_textures; 

	/// ī�޶� ����
	D2DCamera* m_camera;
};

