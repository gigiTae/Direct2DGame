#include "GameProcessPCH.h"
#include "InputManager.h"

InputManager::InputManager()
	:m_matchVK{
		VK_LEFT, // LEFT,
		VK_RIGHT, // RIGHT,
		VK_UP, // UP,
		VK_DOWN, // DOWN,

		'Q',
		'W',
		'E',
		'R',
		'T',
		'Y',
		'U',
		'O',
		'P',
		'A',
		'S',
		'D',
		'F',
		'G',
		'Z',
		'X',
		'C',
		'V',
		'B',

		VK_MENU, // ALT,
		VK_CONTROL, // CTRL,
		VK_LSHIFT, // LSHIFT,
		VK_SPACE, // SPACE,
		VK_RETURN, // ENTER,
		VK_ESCAPE, // ESC,

		VK_LBUTTON, // LBTN
		VK_RBUTTON, // RBTN
	}
	, m_keyInfo{}
	,m_hwnd(nullptr)
{
}

InputManager::~InputManager()
{
}



void InputManager::Initalize(HWND _main)
{
	m_hwnd = _main;

	for (int i = 0; i < static_cast<int>(KEY::LAST); ++i)
	{
		m_keyInfo.push_back(KeyInfo{ KEY_STATE::NONE,false });
	}
}

void InputManager::Update()
{
	HWND hWnd = GetFocus();

	// 현재 포커스중일때
	if (nullptr != hWnd)
	{
		for (int i = 0; i < static_cast<int>(KEY::LAST); ++i)
		{
			if (GetAsyncKeyState(m_matchVK[i] & 0x8000))
			{
				if (m_keyInfo[i].prevPush)
				{
					m_keyInfo[i].state = KEY_STATE::HOLD;
				}
				else
				{
					m_keyInfo[i].state = KEY_STATE::TAP;
				}
				m_keyInfo[i].prevPush = true;
			}
			else
			{
				if (m_keyInfo[i].prevPush)
				{
					m_keyInfo[i].state = KEY_STATE::AWAY;
				}
				else
				{
					m_keyInfo[i].state = KEY_STATE::NONE;
				}
				m_keyInfo[i].prevPush = false;
			}
		}


		// Mouse 위치 계산
		POINT mousePosition{};
		GetCursorPos(&mousePosition);

		ScreenToClient(m_hwnd, &mousePosition);

		m_mousePosition = Vector2(static_cast<float>(mousePosition.x)
			, static_cast<float>(mousePosition.y));

	}
	// 포커스해제되어 예외처리 진행
	else
	{ 
		for (int i = 0; i < static_cast<int>(KEY::LAST); ++i)
		{
			m_keyInfo[i].prevPush = false;
			if (KEY_STATE::TAP == m_keyInfo[i].state || KEY_STATE::HOLD == m_keyInfo[i].state)
			{
				m_keyInfo[i].state = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_keyInfo[i].state)
			{
				m_keyInfo[i].state = KEY_STATE::NONE;
			}

		}
	}
}



void InputManager::Finalize()
{
	
}

bool InputManager::IsKeyState(KEY _key, KEY_STATE _state)
{
	if (_state == GetKeyState(_key))
	{
		return true;
	}

	return false;
}
