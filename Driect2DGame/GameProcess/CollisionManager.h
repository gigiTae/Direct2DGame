#pragma once


// 전방선언
class Collider;
class BoxCollider;
class CircleCollier;
class InputManager;
class SceneManager;
class GameObject;



// 충돌정보 
struct Collision
{
	GameObject* otherObject;
	Collider* otherCollider;
	COLLIDER_TYPE type;
};

/// <summary>
///  충동을 관리하는 매니져이다.
/// 추가기능으로는 다양한 collider를 구현하고 
/// 그에 맞게 매니져는 collider의 종류에 따라서 
/// 충돌정보를 생성하고 전달해준다.
/// </summary>
class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Initalize(InputManager* _inputManager, SceneManager* _sceneManager);
	void Update();
	void Finalize();

private:
	InputManager* m_inputManager;
	SceneManager* m_sceneManager;

};

