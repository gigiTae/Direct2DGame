#pragma once

#include "MonoBehaviour.h"

/// <summary>
/// ����� ȿ���� ����Ѵ�
/// </summary>

struct LineInfo 
{
	Vector2 position;
	float length;
	D2D1::ColorF color;
};

class BackgroundEffect : public MonoBehaviour
{
public:
	BackgroundEffect();
	~BackgroundEffect();


	void Update(float _deltaTime) override;

	void Render(D2DRenderer* _d2DRenderer) override;
	

	
	void SetEffect(float _lineSpeed, float _productSpeed);

private:
	void LineRender(D2DRenderer* _d2DRenderer, const LineInfo& _lineInfo);
	ColorF GetRandomColor();
private:
	list<LineInfo> m_lineList; // ������ ������ ��Ƶδ� �迭

	float m_lineSpeed; // ���ε��� �̵��ӵ�
	float m_elapsedTime; 
	float m_productionSpeed; // ���λ���ӵ�
};

