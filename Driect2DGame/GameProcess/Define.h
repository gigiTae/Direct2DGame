#pragma once

class GameObject;
class Collider;

///  ================= 씬관련 ===========================

enum class SCENE_TYPE
{
	MAIN,
	TOOL,


	NONE, // 다음씬이 없다는 표시
	END, // 게임 종료시에 호출
};

/// ===================== 오브젝트 ==============================

/// <summary>
/// 오브젝트의 타입의 번호가 작을수록 모든 이벤트에서
/// 우선순위를 가진다, 다른의미로 큰 번호일 수록 가장 상단에
/// 랜더링한다.
/// </summary>
enum class OBJECT_TYPE
{
	BACKGROUND,
	UNIT,
	ENEMY,

	ATTACK_EFFECT,
	MOUSE_EFFECT,



	/// 아래의 오브젝트 타입부터는 마우스 이벤트가 발생함
	BACK_UI = 30,	/// 항상 FRONT UI보다 뒤에 그려진다
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
/// 컴포넌트의 호출 순서를 명시함
/// 낮은 숫자일수록 자료구조 맵에서 앞쪽에 정렬되어
/// 게임오브젝트의 업데이트에서 항상 앞쪽 먼저 업데이트를 호출한다.
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

/// =================================== 컴포넌트 관련 ==============================
enum class COLLIDER_TYPE
{
	CIRCLE,
	BOX,
};

// 가장 기본적인 트랜스폼 컴포넌트의 정보를 저장한다.
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

// BarUI를 만드는데 필요한 정보들
struct BarUIInfo
{
	Vector2 positionOffset; // object와 떨어진 거리
	Vector2 innerBarOffset; // 내부바와 가장자리 바의 오프셋
	Vector2 barScale; // 바의 크기 
	float barLength; // 현재 바의 길이 0.f~ 1.f
	
	D2D1::ColorF innerFillBarColor = D2D1::ColorF(ColorF::Black);  // 내부를 채우는 바의 색
	D2D1::ColorF innerEmptyBarColor = D2D1::ColorF(ColorF::Red); // 내부빈공간 바의 색
	D2D1::ColorF edgeColor = D2D1::ColorF(ColorF::White);// 외부 바의 색
};


/// ========================= 충돌 관련 =========================================
// 충돌정보 
struct Collision
{
	GameObject* otherObject;
	Collider* otherCollider;

	Collider* myCollider;
};






///  ================================== 키입력관련 =================================
enum class KEY_STATE
{
	TAP, // 막 누른 시점
	HOLD, // 누르고 있는
	AWAY, // 막 뗀 시점
	NONE, // 눌리지 않았고, 이전에도 눌리지 않은 상태
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

	LAST, //enum의 끝
};
