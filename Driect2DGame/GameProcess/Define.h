#pragma once

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
	GROUND_UNIT,
	AIR_UNIT,

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
