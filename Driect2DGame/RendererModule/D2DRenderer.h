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
	// �׸��� �Լ��� �߰�
	void DrawLine(Vector2 _start, Vector2 _end, COLORREF color = COLORREF(RGB(0, 0, 0)));

private:
	// ����Ÿ���� ����� �Լ�
	HRESULT CreateDeviceResources();

private: 
	// ���� ������ �ڵ�
	HWND m_hwnd;
	ID2D1Factory* m_direct2DFactory;
	ID2D1HwndRenderTarget* m_renderTarget;
	
	IDWriteFactory* m_writeFactory;
	IDWriteTextFormat* m_textFormat;

private:
	// ����̽� �������� �ڿ����� �غ�Ǿ��°�?
	HRESULT m_IsD2DResReady;
	D2D1_SIZE_F m_renderTargetSize;

};

