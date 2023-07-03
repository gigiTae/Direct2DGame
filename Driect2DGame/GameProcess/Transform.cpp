#include "GameProcessPCH.h"
#include "Transform.h"
#include "GameObject.h"

Transform::Transform()
	:Component(CALL_ORDER::TRANSFORMM,typeid(this).name())
	,m_position{}
	,m_rotation(0.f)
	,m_scale{}
	,m_parent(nullptr)
	,m_children{}
	,m_rotationOffset(0.f)
	,m_positionOffset(0.f,0.f)
{}

Transform::~Transform()
{
}

void Transform::SetRotation(float _rotation)
{
	m_rotation = _rotation;
	// 각도값을 조정
	if (m_rotation >= FMath::TwoPI)
	{
		m_rotation -= FMath::TwoPI;
	}

	if (m_rotation < -0.f)
	{
		m_rotation += FMath::TwoPI;
	}
}

void Transform::AddRotation(float _radian)
{
	m_rotation += _radian;
	// 각도값을 조정
	if (m_rotation >= FMath::TwoPI)
	{
		m_rotation -= FMath::TwoPI;
	}

	if (m_rotation < -0.f)
	{
		m_rotation += FMath::TwoPI;
	}
}

void Transform::LateUpdate(float _deltaTime, InputManager* _inputManager)
{
	// 최상단의 부모만 자식들의 움직임을 관리하는 구조이다.
	if (m_parent != nullptr || m_children.empty())
		return;

	// BFS로 해결해볼까? 오랜만에 queue를 사용해보자
	queue<GameObject*> q;

	// 최상단 부모오브젝트에 삽입
	q.push(GetGameObject());;

	while (!q.empty())
	{
		GameObject* object = q.front();

		Transform* transform = object->GetComponent<Transform>();

		// 트랜스폼을 추가를 안했다고?
		assert(transform);

		transform->AlignParentPosition();
		const vector<GameObject*>& children = transform->GetChildren();

		for (auto child : children)
		{
			q.push(child);
		}
		q.pop();
	}
}

void Transform::DebugRender(D2DRenderer* _d2DRenderer)
{
	Vector2 pos = GetPosition();
	float rotation = GetRotation();

	wstring info = L"\nX:" + std::to_wstring(static_cast<int>(pos.x))
		+ L"\nY:" + std::to_wstring(static_cast<int>(pos.y))
		+ L"\nAngle:" + std::to_wstring(static_cast<int>(FMath::Rad2Deg(rotation)));

	_d2DRenderer->DrawTextW(info, pos, Vector2(pos.x + 200.f, pos.y), D2D1::ColorF::Gold);
}

GameObject* Transform::GetChild(int _index)
{
	if (static_cast<int>(m_children.size()) > _index)
	{
		return m_children[_index];
	}

	return nullptr;
}

GameObject* Transform::GetChild(const string& _name)
{
	for (int i = 0; i < static_cast<int>(m_children.size()); ++i)
	{
		const string& name = m_children[i]->GetName();
		if (name == _name)
		{
			return m_children[i];
		}
	}
	return nullptr;
}

void Transform::AddChild(GameObject* _child)
{
	// 만약같은 오브젝트를 두번이나 추가해주는 사람은 없겠지???? 이런것도 예외처리해아하나
	for (auto child : m_children)
	{
		assert(child->GetName() != _child->GetName() || !(L"같은 오브젝트를 두번이 자식으로 추가하였습니다 ? 자네는 무슨의도인가"));
	}

	// 서로를 연결해준다 하지만 SetParent함수를 public로 사용하기 때문에
	// 순환참조하는 지옥이 발생 가능해짐 이에 대한 해결 방법이 필요해 보인다
	m_children.push_back(_child);
	_child->SetParent(GetGameObject());
}

void Transform::SetParent(GameObject* _parent)
{
	///  부모쪽 예외처리
	if (m_parent != nullptr)
	{
		vector<GameObject*>& sibling = m_parent->GetChildren();
		
		for (auto iter = sibling.begin(); iter != sibling.end();)
		{
			if ((*iter)->GetName() == GetName())
			{
				iter = sibling.erase(iter);
			}
			else 
			{
				++iter;
			}
		}
	}

	m_parent = _parent;
}

void Transform::AlignParentPosition()
{
	GameObject* parent = GetParent();
	if (parent == nullptr)
		return;

	/// 부모 오브젝트와 위치를 맞추는 함수
	Transform* parentTransform = parent->GetComponent<Transform>();
	assert(parentTransform);

	Vector2 parentPosition = parentTransform->GetPosition();
	float parentRotation = parentTransform->GetRotation();

	m_position = Vector2::RotateRadian(parentPosition+m_positionOffset, parentPosition, parentRotation);

	SetRotation(parentRotation + m_rotationOffset);
}

