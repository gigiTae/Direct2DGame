#pragma once

enum class SCENE_TYPE
{
	MAIN,
	TOOL,

	END,
};

enum class OBJECT_TYPE
{
	BACKGROUND,
	MONSTER,
	PLAYER,

	
	UI = 31,
	END = 32,
};

enum class COLLIDER_TYPE
{
	CIRCLE,
	BOX,
};

/// <summary>
/// ������Ʈ�� ȣ�� ������ �����
/// ���� �����ϼ��� �켱���� ť�� ���ʿ� ���ĵǾ�
/// ���ӿ�����Ʈ�� ������Ʈ���� �׻� ���� ���� ������Ʈ�� ȣ���Ѵ�.
/// </summary>
enum class CALL_ORDER
{
	DS,

};