#include "GameProcessPCH.h"
#include "BackgroundEffect.h"

BackgroundEffect::BackgroundEffect()
	:MonoBehaviour(typeid(this).name())
	,m_elapsedTime(0.f)
	,m_lineList{}
	,m_lineSpeed(0.f)
	,m_productionSpeed(0.f)
{

}

BackgroundEffect::~BackgroundEffect()
{

}

void BackgroundEffect::Update(float _deltaTime)
{
	m_elapsedTime += _deltaTime;
	
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 110);
	float randomfloat1 = static_cast<float>((dis(gen)));
	float randomfloat2 = static_cast<float>((dis(gen)));
	// 일정한 주기로 라인을 생성한다
	if (m_elapsedTime >= m_productionSpeed)
	{
		m_elapsedTime -= m_productionSpeed;
		LineInfo info{ Vector2(-2000.f - randomfloat1,100.f), 2.f, GetRandomColor()};
		m_lineList.push_back(std::move(info));

		LineInfo info2{ Vector2(-2000.f - randomfloat2,-100.f), 2.f, GetRandomColor()};
		m_lineList.push_back(std::move(info2));
	}

	// 라인들의 위치를 업데이트한다.

	for (auto iter = m_lineList.begin(); iter !=  m_lineList.end();)
	{
		iter->position.x += _deltaTime * m_lineSpeed;

		if (iter->position.x >= 1920.f)
		{
			iter = m_lineList.erase(iter);
		}
		else
			++iter;
	}
}

void BackgroundEffect::Render(D2DRenderer* _d2DRenderer)
{
	// 가지고 있는 라인들을 랜더링한다.
	for (auto& line : m_lineList)
	{
		LineRender(_d2DRenderer, line);
	}
}

void BackgroundEffect::SetEffect(float _lineSpeed, float _productSpeed)
{
	m_lineSpeed = _lineSpeed;
	m_productionSpeed = _productSpeed;
}

void BackgroundEffect::LineRender(D2DRenderer* _d2DRenderer, const LineInfo& _lineInfo)
{
	Vector2 startPoint = _lineInfo.position;
	Vector2 endPoint{ startPoint.x + _lineInfo.length * 5.f, startPoint.y + _lineInfo.length };

	_d2DRenderer->DrawFillRectangle2(startPoint, endPoint, _lineInfo.color);
	//_d2DRenderer->DrawRectangle(startPoint, endPoint, _lineInfo.color);
}

D2D1::ColorF BackgroundEffect::GetRandomColor()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 10);
	int randomInt = dis(gen);

	ColorF color = ColorF::Black;

	switch (randomInt)
	{
	case 0:
	{
		color = ColorF::Ivory;
	}
	break;
	case 1:
	{
		color = ColorF::LightBlue;
	}
	break;
	case 2:
	{
		color = ColorF::LightCyan;
	}
	break;
	case 3:
	{
		color = ColorF::LightPink;
	}
	break;
	case 4:
	{
		color = ColorF::LightGreen;
	}
	break;
	case 5:
	{
		color = ColorF::LightYellow;
	}
	break;
	case 6:
	{
		color = ColorF::LightSeaGreen;
	}
	break;
	case 7:
	{
		color = ColorF::LightPink;
	}
	break;
	case 8:
	{
		color = ColorF::PaleVioletRed;
	}
	break;
	case 9:
	{
		color = ColorF::BlueViolet;
	}
	break;

	case 10:
	{
		color = ColorF::LightGoldenrodYellow;
	}
	break;
	default:
		break;
	}

	return color;
}
