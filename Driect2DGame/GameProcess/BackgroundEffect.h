#pragma once

#include "MonoBehaviour.h"

/// <summary>
/// 배경의 효과를 담당한다
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
	list<LineInfo> m_lineList; // 라인의 정보를 담아두는 배열

	float m_lineSpeed; // 라인들의 이동속도
	float m_elapsedTime; 
	float m_productionSpeed; // 라인생산속도
};

