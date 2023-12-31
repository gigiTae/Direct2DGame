#pragma once

class D2DTexture;
class D2DCamera;

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
	void Finalize();

	void BeginRender();
	void EndRender();

public:
	// 화면에 오보젝트가 카메라에 영향을 받는지 확인하는 함수
	void SetCameraAffected(bool _isAffected);

private:
	void SetTransform(float _radian, Vector2 _point);
	// 기본 행렬로 변환
	void SetTransform() { m_deviceContext->SetTransform(m_finalMatrix); }
public:
	/// 그리기 관련 함수들

	// 직선을 그리는 함수
	void DrawLine(Vector2 _point1, Vector2 _point2
		, ColorF = D2D1::ColorF::White);

	void DrawEllipse(Vector2 _point, Vector2 _radius
		, COLORREF = D2D1::ColorF::White);

	void DrawEllipse(Vector2 _point, float _radius,
		COLORREF color = D2D1::ColorF::White);

	// 사각형 그리는 함수
	void DrawRectangle(Vector2 _leftTop, Vector2 _rightBottom
		, ColorF color = D2D1::ColorF::White, float _rotation = 0.f);

	// 내부를 채우는 사각형 그리기
	void DrawFillRectangle(Vector2 _position, Vector2 _scale
		, ColorF color = D2D1::ColorF(ColorF::White,1.f), float _rotation = 0.f);

	void DrawFillRectangle2(Vector2 _leftTop, Vector2 _rightBottom
		, ColorF color = ColorF(ColorF::WhiteSmoke),float _rotation = 0.f);

	// 텍스트 출력함수 
	void DrawTextW(const std::wstring& _str, Vector2 _leftTop
		, Vector2 _rightBottom, ColorF _color = D2D1::ColorF::White);

public:
	// 비트맵 로드
	D2DTexture* LoadBitMap(const wstring& _key, const wchar_t* _filePath);

	void DrawBitMap(const wstring& _key, Vector2 _position
		, float _rotation = 0.f, float _alpha = 1.f);

	// 텍스처를 잘라서 랜더링
	void DrawBitMap(const wstring& _key, Vector2 _position
		, Vector2 _textureLeftTop, Vector2 _sliceSize
		, float _rotation = 0.f, float _alpha = 1.f);
	
	/// 카메라 관련
	D2DCamera* GetCamera()const { return m_camera; }

private:
	HRESULT LoadBitmapFromFile(PCWSTR _filePath
		, UINT _destinationWidth, UINT _destinationHeight, ID2D1Bitmap** _bitmap);

	// 이펙트 생성
	void CreateEffects();

private:
	/// 랜더타겟을 만드는 함수
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();

	//HRESULT LoadBitmapFromFile()
private:
	D2D1_MATRIX_3X2_F m_screenMatrix; // 스크린 좌표계로 변환하는 행렬
	D2D1_MATRIX_3X2_F m_finalMatrix;

	// 메인 윈도우 핸들
	HWND m_hwnd;
	ID2D1Factory1* m_factory; // 버전업한 팩토리

	// 쓰기 전용 
	IDWriteFactory* m_writeFactory;
	IDWriteTextFormat* m_textFormat;

	// 브러쉬
	ID2D1SolidColorBrush* m_tempBrush; // 잠시 사용하는 용도

	ID2D1DeviceContext* m_deviceContext; 
	D3D_FEATURE_LEVEL m_featureLevel; 
	ID2D1Device* m_device; // D2D Deivice;
	IDXGISwapChain1* m_swapChain; // 스왑체인
	ID2D1Bitmap1* m_targetBitmap;
	float m_dpi;

	ID2D1Effect* m_d2dEffect[static_cast<int>(D2DEFFECT::END)];
private:
	// 디바이스 종속적인 자원들이 준비되었는가?
	HRESULT m_IsD2DResReady;
	D2D1_SIZE_F m_renderTargetSize;

private:
	bool m_cameraAffected;

	/// 비트맵 관련 
	IWICImagingFactory* m_imagingFactorty;

	/// 텍스처를 저장하는 공간
	map<wstring, D2DTexture*> m_textures; 

	/// 카메라 관련
	D2DCamera* m_camera;
};

