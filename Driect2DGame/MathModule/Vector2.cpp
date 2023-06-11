#include "MathModulePCH.h"
#include "Vector2.h"

const Vector2 Vector2::UnitX{ 1.f,0.f };
const Vector2 Vector2::UnitY{ 0.f, 1.f };
const Vector2 Vector2::One{ 1.f, 1.f };
const Vector2 Vector2::Zero{ 0.f,0.f };

std::string Vector2::ToString() const
{
	char result[64];
	std::snprintf(result, sizeof(result), "(%.3f, %.3f)", x, y);
	return result;
}


void Vector2::Normalize()
{
	*this = GetNormalize();
}

Vector2 Vector2::GetNormalize() const
{
	float squarSum = SizeSquared();
	if (squarSum == 1.f)
	{
		return *this;
	}
	else if (squarSum == 0.f)
	{
		return Vector2::Zero;
	}

	// ��� �� ������ ������ ����ϸ� ���� ���� ����

	float invLength = 1 / sqrtf(squarSum);

	return Vector2(x, y) * invLength;
}