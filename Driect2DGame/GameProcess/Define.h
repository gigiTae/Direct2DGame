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
/// 컴포넌트의 호출 순서를 명시함
/// 낮은 숫자일수록 우선순위 큐에 앞쪽에 정렬되어
/// 게임오브젝트의 업데이트에서 항상 앞쪽 먼저 업데이트를 호출한다.
/// </summary>
enum class CALL_ORDER
{
	DS,

};