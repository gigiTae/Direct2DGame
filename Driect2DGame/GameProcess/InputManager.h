#pragma once

enum class KEY_STATE
{
	TAP, // �� ���� ����
	HOLD, // ������ �ִ�
	AWAY, // �� �� ����
	NONE, // ������ �ʾҰ�, �������� ������ ���� ����
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LBTN,
	RBTN,

	LAST, //enum�� ��

};

struct KeyInfo
{
	KEY_STATE state; // Ű�� ���°�
	bool      prevPush;  // ���� �����ӿ��� ���ȴ��� ����
};

/// <summary>
/// �Է��� ������ش�.
/// Ű����, ���콺���� �Էµ����͸� �����Ӹ��� �����Ͽ�
/// �����ϰ� ����Ѵ�.
/// 
/// </summary>
class InputManager
{
public:
	InputManager();
	~InputManager();

	void Initalize(HWND _main);
	void Update();
	void Finalize();

	KEY_STATE GetKeyState(KEY _key) { return m_keyInfo[static_cast<int>(_key)].state; }
	bool IsKeyState(KEY _key, KEY_STATE _state);
private:

	// ���� ������ �ڵ�
	HWND m_hwnd;

	// �̹� ������ ���콺 ��ġ
	Vector2 m_mousePosition;

	// Ű �������� ���� �迭
	vector<KeyInfo> m_keyInfo;

	// KEY ���� ����Ű���� ��Ī�����ִ� �迭
	const int m_matchVK[static_cast<int>(KEY::LAST)];
};
