#pragma once


enum class SCENE_TYPE
{
	MAIN,
	TOOL,

	END,
};

/// <summary>
/// 오브젝트의 타입의 번호가 작을수록 모든 이벤트에서
/// 우선순위를 가진다, 다른의미로 큰 번호일 수록 가장 상단에
/// 랜더링한다.
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


enum class COLLIDER_TYPE
{
	CIRCLE,
	BOX,
};


