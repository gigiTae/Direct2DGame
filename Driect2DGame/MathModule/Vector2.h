#pragma once


struct Vector2
{
public:
	float x;
	float y;
	
	inline constexpr Vector2():x(0.f),y(0.f){}
	inline explicit constexpr Vector2(int _x, int _y);
	inline explicit constexpr Vector2(float _x, float _y);

	/// ������
	inline constexpr Vector2 operator-() const;
	inline constexpr Vector2 operator*(float _scalar) const;
	inline constexpr Vector2 operator/(float _scalar) const;
	inline constexpr Vector2 operator*(const Vector2& _other) const;
	inline constexpr Vector2 operator+(const Vector2& _other) const;
	inline constexpr Vector2 operator-(const Vector2& _other) const;
	inline constexpr Vector2& operator*=(float _scale);
	inline constexpr Vector2& operator/=(float _scale);
	inline constexpr Vector2& operator+=(const Vector2& _other);
	inline constexpr Vector2& operator-=(const Vector2& _other);
	inline constexpr bool operator==(const Vector2& _other);
	inline constexpr bool operator!=(const Vector2& _other);


	// ��Ʈ ������ (����)
	inline float Size() const;

	// ������ ��ȯ
	inline constexpr float SizeSquared() const;

	// ���� ����ȭ
	void Normalize();

	// [[nodiscard]] : ��ȯ���� ���� ������ ���
	[[nodiscard]] Vector2 GetNormalize() const;

	// ��ȯ���� �����Դϴ�!!
	inline float Angle() const;

	// ���� ��ǥ�� -> ����ǥ�� ��ȯ
	inline Vector2 ToPolarCoordinate() const;

	// ����ǥ�� -> ������ǥ�� ��ȯ
	inline Vector2 ToCartesianCoordinate() const;

	// ��������
	inline constexpr float Dot(const Vector2& _other) const;

	
	std::string ToString() const;
	
	inline D2D1_POINT_2F ToPoint2F();

	// �����������
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 One;
	static const Vector2 Zero;


};

inline D2D1_POINT_2F Vector2::ToPoint2F()
{
	D2D1_POINT_2F point;
	point.x = x;
	point.y = y;
	return point;
}

inline constexpr Vector2::Vector2(int _x, int _y)
	:x((float)_x)
	, y((float)_y)
{}

inline constexpr Vector2::Vector2(float _x, float _y)
	: x(_x)
	, y(_y)
{}

inline constexpr Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

inline constexpr Vector2 Vector2::operator*(float _scalar) const
{
	return Vector2(x * _scalar, y * _scalar);
}

inline constexpr Vector2 Vector2::operator/(float _scalar) const
{
	return Vector2(x / _scalar, y / _scalar);
}

inline constexpr Vector2 Vector2::operator*(const Vector2& _other) const
{
	return Vector2(x * _other.x, y * _other.y);
}

inline constexpr Vector2 Vector2::operator+(const Vector2& _other) const
{
	return Vector2(x + _other.x, y + _other.y);
}

inline constexpr Vector2 Vector2::operator-(const Vector2& _other) const
{

	return Vector2(x - _other.x, y - _other.y);
}

inline constexpr Vector2& Vector2::operator*=(float _scale)
{
	x *= _scale;
	y *= _scale;

	return *this;
}

inline constexpr Vector2& Vector2::operator/=(float _scale)
{
	x /= _scale;
	y /= _scale;

	return *this;
}

inline constexpr Vector2& Vector2::operator+=(const Vector2& _other)
{
	x += _other.x;
	y += _other.y;

	return *this;
}

inline constexpr Vector2& Vector2::operator-=(const Vector2& _other)
{
	x -= _other.x;
	y -= _other.y;

	return *this;
}

inline constexpr bool Vector2::operator==(const Vector2& _other)
{
	return (x == _other.x && y == _other.y);
}

inline constexpr bool Vector2::operator!=(const Vector2& _other)
{
	return (x != _other.x || y != _other.y);
}

inline float Vector2::Size() const
{
	return sqrtf(SizeSquared());
}

inline constexpr float Vector2::SizeSquared() const
{
	return x * x + y * y;
}

inline float Vector2::Angle() const
{
	return atan2f(y, x);
}


inline Vector2 Vector2::ToPolarCoordinate() const
{
	return Vector2(Size(), Angle());
}

inline Vector2 Vector2::ToCartesianCoordinate() const
{
	// ����ǥ�迡���� x�� ������ y�� ��(rad)���� Ȱ��
	float sinValue = sinf(y);
	float cosValue = cosf(y);

	return Vector2(x * sinValue, x * cosValue);
}

inline constexpr float Vector2::Dot(const Vector2& _other) const
{
	return x* _other.x + y * _other.y;
}
