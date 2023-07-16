#pragma once

class GameObject;
class Collider;

///  ================= ������ ===========================

enum class SCENE_TYPE
{
	MAIN,
	TOOL,


	NONE, // �������� ���ٴ� ǥ��
	END, // ���� ����ÿ� ȣ��
};

/// ===================== ������Ʈ ==============================

/// <summary>
/// ������Ʈ�� Ÿ���� ��ȣ�� �������� ��� �̺�Ʈ����
/// �켱������ ������, �ٸ��ǹ̷� ū ��ȣ�� ���� ���� ��ܿ�
/// �������Ѵ�.
/// </summary>
enum class OBJECT_TYPE
{
	BACKGROUND,
	UNIT,
	ENEMY,

	ATTACK_EFFECT,
	MOUSE_EFFECT,



	/// �Ʒ��� ������Ʈ Ÿ�Ժ��ʹ� ���콺 �̺�Ʈ�� �߻���
	BACK_UI = 30,	/// �׻� FRONT UI���� �ڿ� �׷�����
	FRONT_UI = 31,
	END = 32,
};


enum class OBJECT_STATE
{
	ALIVE,
	TO_BE_DESTORYED,
	DESTORY,
};

/// <summary>
/// ������Ʈ�� ȣ�� ������ �����
/// ���� �����ϼ��� �ڷᱸ�� �ʿ��� ���ʿ� ���ĵǾ�
/// ���ӿ�����Ʈ�� ������Ʈ���� �׻� ���� ���� ������Ʈ�� ȣ���Ѵ�.
/// </summary>
enum class CALL_ORDER
{
	MONO_BEHAVIOUR,
	RENDERER,
	ANIMATOR,
	RIGID_BODY,
	TRANSFORMM,
	COLLIDER,
	UI
};

/// =================================== ������Ʈ ���� ==============================
enum class COLLIDER_TYPE
{
	CIRCLE,
	BOX,
};

// ���� �⺻���� Ʈ������ ������Ʈ�� ������ �����Ѵ�.
struct TransformInfo
{
	TransformInfo() = default;
	TransformInfo(Vector2 _position, Vector2 _scale, float _rotation = 0.f)
		:position(_position), scale(_scale), rotation(_rotation)
	{}

	Vector2 position = Vector2::Zero;
	Vector2 scale = Vector2::One;
	float rotation = 0.f;
};

struct BoxColliderInfo
{
	BoxColliderInfo(Vector2 _offset = Vector2::Zero, Vector2 _scale =Vector2::Zero
		, bool _rotatable = false, bool _isTrigger = false)
		: offsetPosition(_offset),scale(_scale),rotatable(_rotatable)
		, isTrigger(_isTrigger)
	{}

	Vector2 offsetPosition;
	Vector2 scale;
	bool isTrigger; 
	bool rotatable;
};

struct CircleInfo
{
	CircleInfo(Vector2 _offset, float _radius, bool _isTrigger = false)
		:radius(_radius), positionOffset(_offset)
		,isTrigger(_isTrigger)
	{}

	bool isTrigger;
	Vector2 positionOffset = Vector2::Zero;
	float radius = 0.f;
};

// BarUI�� ����µ� �ʿ��� ������
struct BarUIInfo
{
	Vector2 positionOffset; // object�� ������ �Ÿ�
	Vector2 innerBarOffset; // ���ιٿ� �����ڸ� ���� ������
	Vector2 barScale; // ���� ũ�� 
	float barLength; // ���� ���� ���� 0.f~ 1.f
	
	D2D1::ColorF innerFillBarColor = D2D1::ColorF(ColorF::Black);  // ���θ� ä��� ���� ��
	D2D1::ColorF innerEmptyBarColor = D2D1::ColorF(ColorF::Red); // ���κ���� ���� ��
	D2D1::ColorF edgeColor = D2D1::ColorF(ColorF::White);// �ܺ� ���� ��
};


/// ========================= �浹 ���� =========================================
// �浹���� 
struct Collision
{
	GameObject* otherObject;
	Collider* otherCollider;

	Collider* myCollider;
};






///  ================================== Ű�Է°��� =================================
enum class KEY_STATE
{
	TAP, // �� ���� ����
	HOLD, // ������ �ִ�
	AWAY, // �� �� ����
	NONE, // ������ �ʾҰ�, �������� ������ ���� ����
};

enum class KEY
{
	LEFT, RIGHT, UP, DOWN,

	Q, W, E, R, T, Y, U, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,

	ALT, CTRL, LSHIFT,
	SPACE, ENTER, ESC, TAB,

	LMOUSE, RMOUSE,
	F1, F2, F3, F4, F5,

	LAST, //enum�� ��
};
