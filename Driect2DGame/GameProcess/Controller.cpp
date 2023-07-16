#include "GameProcessPCH.h"
#include "Controller.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"
#include "CameraManager.h"
#include "Unit.h"
#include "TextureRenderer.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "CameraManager.h"


Controller::Controller()
	:MonoBehaviour(typeid(this).name())
	,m_dragEnd{}
	,m_dragStart{}
	,m_isDragging(false)
	,m_selectUnits{}
	,m_currentMousePosition(Vector2::Zero)
	,m_onMouseUnit(nullptr)
{

}

Controller::~Controller()
{

}

void Controller::Render(D2DRenderer* _d2DRenderer)
{
	
	// �簢�� �׸���
	if (m_isDragging)
		_d2DRenderer->DrawRectangle(m_dragStart, m_dragEnd, D2D1::ColorF::Green);
	// ���콺��ġ�� ������Ʈ�� ������ ǥ��
	else if (m_onMouseUnit)
	{
		const CameraManager* camera = GetCameraManager();
		Vector2 cameraMousePosition = camera->WorldToCamera(m_currentMousePosition);

		_d2DRenderer->DrawBitMap(L"OnMouseEffect", cameraMousePosition);
	}

}

void Controller::Update(float _deltaTime)
{
	// ���� ������ ������Ʈ ó��
	for (auto iter = m_selectUnits.begin(); iter != m_selectUnits.end();)
	{
		if (!(*iter)->IsAlive())
		{
			iter = m_selectUnits.erase(iter);
		}
		else
			++iter;
	}
	
	SearchOnMouseUnit();
	// ���õ� �δ뿡�� ��ɳ�����
	OrderSelectUnits();
}

void Controller::OnMouseDown()
{
	/// ó������ �δ����� ����
	const InputManager* input = GetInputManager();
	Vector2 mouse = input->GetCameraMousePosition();

	m_isDragging = true;
	m_dragStart = mouse;
}

void Controller::OnMouse()
{
	/// �簢�� ������ 
	const InputManager* input = GetInputManager();
	Vector2 mouse = input->GetCameraMousePosition();

	m_dragEnd = mouse;
}

void Controller::OnMouseUp()
{
	m_isDragging = false;
	
	/// �δ� ���� �Լ� �߰�
	GetUnits();
}

void Controller::OrderSelectUnits()
{
	const InputManager* input = GetInputManager();


	// �δ� �̵� �̺�Ʈ �߻�
	if (input->IsKeyState(KEY::RMOUSE, KEY_STATE::TAP))
	{
		const SceneManager* sceneMgr = GetSceneManager();

		// ī�޶� ��ǥ���� ���콺 ������
		Vector2 cameraMousePosition = input->GetCameraMousePosition();

		GameObject* effect1 = new GameObject("mouseEffect", GetManagerSet(), OBJECT_TYPE::MOUSE_EFFECT);
		effect1->CreateComponent<TextureRenderer>()->SetKey(L"MouseEffect1");
		effect1->CreateComponent<Transform>()->SetPosition(cameraMousePosition);
		effect1->Destory(0.15f);
		effect1->SetCameraAffected(false);
		sceneMgr->RegisterObject(effect1);

		// ������Ʈ���� �̵������ �����Ѵ�.

		Vector2 worldMousePostion = input->GetWorldMousePosition();

		for (auto object : m_selectUnits)
		{
			Unit* unit = object->GetComponent<Unit>();
			unit->MoveUnit(worldMousePostion);
		}
	}
	else if (input->IsKeyState(KEY::H, KEY_STATE::HOLD))
	{
		// ������ �δ뿡�� ���� ����� �����Ѵ�.
		for (auto object : m_selectUnits)
		{
			Unit* unit = object->GetComponent<Unit>();
			unit->HoldUnit();
		}
	}
	else if (input->IsKeyState(KEY::A, KEY_STATE::TAP) && m_onMouseUnit)
	{
		// ������ �δ뿡�� ���� ����� �����Ѵ�.
		for (auto object : m_selectUnits)
		{
			Unit* unit = object->GetComponent<Unit>();
			unit->AttackUnit(m_onMouseUnit);
		}
	}

	if (input->IsKeyState(KEY::F4, KEY_STATE::TAP))
	{
		const SceneManager* sceneMgr = GetSceneManager();
		sceneMgr->RegisterNextScene(SCENE_TYPE::MAIN);
	}
}

void Controller::SearchOnMouseUnit()
{
	const InputManager* input = GetInputManager();
	const CollisionManager* collisionMgr = GetCollisionManager();

	m_currentMousePosition = input->GetWorldMousePosition();

	vector<Collider*> colliders{};
	collisionMgr->DetectPointToCollider(m_currentMousePosition, colliders);

	// ���ʹ迭�� ������Ʈ�� �����´�.
	for (auto collider : colliders)
	{
		if (collider->GetColliderType() == COLLIDER_TYPE::BOX)
		{
			m_onMouseUnit = collider->GetGameObject();
			return;
		}
	}

	m_onMouseUnit = nullptr;
}

void Controller::GetUnits()
{
	const CameraManager* camera = GetCameraManager();
	// ī�޶󿡼� ���� ��ǥ��� ��ȯ�Ѵ� 
	Vector2 start = camera->CameraToWorld(m_dragStart);
	Vector2 end = camera->CameraToWorld(m_dragEnd);

	const CollisionManager* collisionMgr = GetCollisionManager();

	// ������ �簢���� Rect�� ���
	Vector2 minArea{}, maxArea{};
	minArea.x = FMath::Min(start.x, end.x);
	minArea.y = FMath::Min(start.y, end.y);
	maxArea.x = FMath::Max(start.x, end.x);
	maxArea.y = FMath::Max(start.y, end.y);

	// ���ʴ�� �簢�����ο� �ִ��� �Ǵ��Ѵ�
	vector<Collider*> selectColliders{};

	// �簢���� ũ�Ⱑ ���� ��� �Ѱ��� ������Ʈ�� �����Ѵ�
	if ((maxArea - minArea).LengthSquared() < 32.f && m_onMouseUnit != nullptr)
	{
		selectColliders.push_back(m_onMouseUnit->GetComponent<Collider>());
	}
	else
	{
		collisionMgr->DetectBoxToCollider(minArea, maxArea, selectColliders);

		// ���� �ݶ��̴��� �迭���� �����Ѵ�.
		for (auto iter = selectColliders.begin(); iter != selectColliders.end();)
		{
			if ((*iter)->GetColliderType() == COLLIDER_TYPE::CIRCLE)
			{
				iter = selectColliders.erase(iter);
			}
			else
				++iter;
		}
	}

	// ���� �簢�� ���ο� ������Ʈ�� ������ ���� �δ븦 �״�� ���
	if (selectColliders.empty())
	{
		return;
	}
	else
	{
		// ���� �δ�� �������� ó��
		for (auto object : m_selectUnits)
		{
			Unit* unit = object->GetComponent<Unit>();
			unit->SetSelct(false);
		}

		// ���������� �δ�� ����
		m_selectUnits.clear();

		for (auto collider : selectColliders)
		{
			m_selectUnits.push_back(collider->GetGameObject());
		}
		
		// ���� ������ �δ뿡 �˸�
		for (auto object : m_selectUnits)
		{
			Unit* unit = object->GetComponent<Unit>();
			unit->SetSelct(true);
		}

	}

}
