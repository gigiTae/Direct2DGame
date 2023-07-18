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

public:
	// ȭ�鿡 ������Ʈ�� ī�޶� ������ �޴��� Ȯ���ϴ� �Լ�
	void SetCameraAffected(bool _isAffected);

private:
	void SetTransform(float _radian, Vector2 _point);
	// �⺻ ��ķ� ��ȯ
	void SetTransform() { m_deviceContext->SetTransform(m_finalMatrix); }
public:
	/// �׸��� ���� �Լ���

	// ������ �׸��� �Լ�
	void DrawLine(Vector2 _point1, Vector2 _point2
		, ColorF = D2D1::ColorF::White);

	void DrawEllipse(Vector2 _point, Vector2 _radius
		, COLORREF = D2D1::ColorF::White);

	void DrawEllipse(Vector2 _point, float _radius,
		COLORREF color = D2D1::ColorF::White);

	// �簢�� �׸��� �Լ�
	void DrawRectangle(Vector2 _leftTop, Vector2 _rightBottom
		, ColorF color = D2D1::ColorF::White, float _rotation = 0.f);

	// ���θ� ä��� �簢�� �׸���
	void DrawFillRectangle(Vector2 _position, Vector2 _scale
		, ColorF color = D2D1::ColorF(ColorF::White,1.f), float _rotation = 0.f);

	void DrawFillRectangle2(Vector2 _leftTop, Vector2 _rightBottom
		, ColorF color = ColorF(ColorF::WhiteSmoke),float _rotation = 0.f);

	// �ؽ�Ʈ ����Լ� 
	void DrawTextW(const std::wstring& _str, Vector2 _leftTop
		, Vector2 _rightBottom, ColorF _color = D2D1::ColorF::White);

public:
	// ��Ʈ�� �ε�
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

	// ����Ʈ ����
	void CreateEffects();

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
	ID2D1Factory1* m_factory; // �������� ���丮

	// ���� ���� 
	IDWriteFactory* m_writeFactory;
	IDWriteTextFormat* m_textFormat;

	// �귯��
	ID2D1SolidColorBrush* m_tempBrush; // ��� ����ϴ� �뵵

	ID2D1DeviceContext* m_deviceContext; 
	D3D_FEATURE_LEVEL m_featureLevel; 
	ID2D1Device* m_device; // D2D Deivice;
	IDXGISwapChain1* m_swapChain; // ����ü��
	ID2D1Bitmap1* m_targetBitmap;
	float m_dpi;

	ID2D1Effect* m_d2dEffect[static_cast<int>(D2DEFFECT::END)];
private:
	// ����̽� �������� �ڿ����� �غ�Ǿ��°�?
	HRESULT m_IsD2DResReady;
	D2D1_SIZE_F m_renderTargetSize;

private:
	bool m_cameraAffected;

	/// ��Ʈ�� ���� 
	IWICImagingFactory* m_imagingFactorty;

	/// �ؽ�ó�� �����ϴ� ����
	map<wstring, D2DTexture*> m_textures; 

	/// ī�޶� ����
	D2DCamera* m_camera;
};

