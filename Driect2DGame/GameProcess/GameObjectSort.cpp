#include "GameProcessPCH.h"
#include "GameObjectSort.h"
#include "GameObject.h"
#include "Transform.h"


bool SortFunction(GameObject* _left, GameObject* _right)
{
	Vector2 leftPosition = _left->GetComponent<Transform>()->GetPosition();
	Vector2 rightPosition = _right->GetComponent<Transform>()->GetPosition();

	if (leftPosition.y > rightPosition.y)
		return true;
	else if (leftPosition.y == rightPosition.y
		&& leftPosition.x < rightPosition.x)
		return true;

	return false;
}
