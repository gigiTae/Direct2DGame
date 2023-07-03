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
	// �������� ����
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
	// �������� ����
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
	// �ֻ���� �θ� �ڽĵ��� �������� �����ϴ� �����̴�.
	if (m_parent != nullptr || m_children.empty())
		return;

	// BFS�� �ذ��غ���? �������� queue�� ����غ���
	queue<GameObject*> q;

	// �ֻ�� �θ������Ʈ�� ����
	q.push(GetGameObject());;

	while (!q.empty())
	{
		GameObject* object = q.front();

		Transform* transform = object->GetComponent<Transform>();

		// Ʈ�������� �߰��� ���ߴٰ�?
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
	// ���ర�� ������Ʈ�� �ι��̳� �߰����ִ� ����� ������???? �̷��͵� ����ó���ؾ��ϳ�
	for (auto child : m_children)
	{
		assert(child->GetName() != _child->GetName() || !(L"���� ������Ʈ�� �ι��� �ڽ����� �߰��Ͽ����ϴ� ? �ڳ״� �����ǵ��ΰ�"));
	}

	// ���θ� �������ش� ������ SetParent�Լ��� public�� ����ϱ� ������
	// ��ȯ�����ϴ� ������ �߻� �������� �̿� ���� �ذ� ����� �ʿ��� ���δ�
	m_children.push_back(_child);
	_child->SetParent(GetGameObject());
}

void Transform::SetParent(GameObject* _parent)
{
	///  �θ��� ����ó��
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

	/// �θ� ������Ʈ�� ��ġ�� ���ߴ� �Լ�
	Transform* parentTransform = parent->GetComponent<Transform>();
	assert(parentTransform);

	Vector2 parentPosition = parentTransform->GetPosition();
	float parentRotation = parentTransform->GetRotation();

	m_position = Vector2::RotateRadian(parentPosition+m_positionOffset, parentPosition, parentRotation);

	SetRotation(parentRotation + m_rotationOffset);
}

