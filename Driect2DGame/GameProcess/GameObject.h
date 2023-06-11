#pragma once


// ���漱��
class Transform;
class BoxCollider;
class CircleCollider;
class InputManager;

/// <summary>
/// ������Ʈ�� �⺻��
/// ������Ʈ ������������ �����ϰ� ������Ʈ�� �����غ���!
/// 
/// </summary>
class GameObject
{

public:
	GameObject() = default;
	virtual ~GameObject();

public:
	void CreateTransform(const Vector2& _position, const Vector2& _scale, float _rotation = 0.f);
	void CreateBoxCollider();
	void CreateCircleCollider();
	
	Transform* GetTransform() { return m_transform; }
	BoxCollider* GetBoxCollider() { return m_boxCollider; }
	CircleCollider* GetCircleCollider() { return m_circleCollider; }
	
	virtual void Initalize() = 0;
	virtual void Update(float _deltaTime, InputManager* inputManager) = 0;
	virtual void Render();
	virtual void Finalize() = 0;

private:
	Transform* m_transform;
	BoxCollider* m_boxCollider;
	CircleCollider* m_circleCollider;


};

