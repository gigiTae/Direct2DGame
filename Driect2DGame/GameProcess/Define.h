#pragma once


enum class SCENE_TYPE
{
	MAIN,
	TOOL,

	END,
};

/// <summary>
/// ������Ʈ�� Ÿ���� ��ȣ�� �������� ��� �̺�Ʈ����
/// �켱������ ������, �ٸ��ǹ̷� ū ��ȣ�� ���� ���� ��ܿ�
/// �������Ѵ�.
/// </summary>
enum class OBJECT_TYPE
{
	BACKGROUND,
	MONSTER,
	PLAYER,

	
	UI = 31,
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


enum class COLLIDER_TYPE
{
	CIRCLE,
	BOX,
};


