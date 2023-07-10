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

Controller::Controller()
	:MonoBehaviour(typeid(this).name())
	,m_dragEnd{}
	,m_dragStart{}
	,m_isDragging(false)
	,m_selectUnits{}
{

}

Controller::~Controller()
{

}

void Controller::Render(D2DRenderer* _d2DRenderer)
{
	if (m_isDragging)
		_d2DRenderer->DrawRectangle(m_dragStart, m_dragEnd, D2D1::ColorF::Green);
}

void Controller::Update(float _deltaTime)
{
	const InputManager* input = GetInputManager();
	
	// �δ� �̵� �̺�Ʈ �߻�
	if (input->IsKeyState(KEY::RMOUSE, KEY_STATE::TAP))
	{
		const SceneManager* sceneMgr = GetSceneManager();
		
		// ī�޶� ��ǥ���� ���콺 ������
		Vector2 cameraMousePosition = input->GetCameraMousePosition();

		GameObject* effect1 = new GameObject("mouseEffect", GetManagerSet());
		effect1->CreateComponent<TextureRenderer>()->SetKey(L"MouseEffect1");
		effect1->CreateComponent<Transform>()->SetPosition(cameraMousePosition);
		effect1->Destory(0.1f);
		effect1->SetCameraAffected(false);
		sceneMgr->RegisterObject(effect1, OBJECT_TYPE::MOUSE_EFFECT);

		// ������Ʈ���� �̵������ �����Ѵ�.

		Vector2 worldMousePostion = input->GetWorldMousePosition();

		for (auto object : m_selectUnits)
		{			Unit* unit = object->GetComponent<Unit>();
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

void Controller::GetUnits()
{
	/// ������ ������Ʈ���� �޾ƿ´� 
	const SceneManager* sceneMgr = GetSceneManager();
	Scene* scene = sceneMgr->GetCurrentScene();

	const CameraManager* camera = GetCameraManager();
	// ī�޶󿡼� ���� ��ǥ��� ��ȯ�Ѵ� 
	Vector2 start = camera->CameraToWorld(m_dragStart);
	Vector2 end = camera->CameraToWorld(m_dragEnd);

	// ������ �簢���� Rect�� ���
	Vector2 minArea{}, maxArea{};
	minArea.x = FMath::Min(start.x, end.x);
	minArea.y = FMath::Min(start.y, end.y);
	maxArea.x = FMath::Max(start.x, end.x);
	maxArea.y = FMath::Max(start.y, end.y);

	// ���ʴ�� �簢�����ο� �ִ��� �Ǵ��Ѵ�
	vector<GameObject*> selectObject;

	// Areaũ�Ⱑ ������ �Ѱ��� ������Ʈ�� �����Ѵ�
	if (maxArea.x - minArea.x <= 5.f && maxArea.y - minArea.y <= 5.f)
	{
		for (int i = static_cast<int>(OBJECT_TYPE::GROUND_UNIT);
			i < static_cast<int>(OBJECT_TYPE::BACK_UI); ++i)
		{
			const vector<GameObject*>& groupObject
				= scene->GetGroupObject(static_cast<OBJECT_TYPE>(i));

			for (auto object : groupObject)
			{
				// AABB�浹�˻� 
				Transform* transform = object->GetComponent<Transform>();
				Vector2 position = transform->GetPosition();
				Vector2 scale = transform->GetScale();

				Vector2 objectMin = position - scale * 0.5f;
				Vector2 objectMax = position + scale * 0.5f;

				// �簢�� ���ο� ������
				if (minArea.x <= objectMax.x && maxArea.x >= objectMin.x
					&& minArea.y <= objectMax.y && maxArea.y >= objectMin.y)
				{
					if (!selectObject.empty())
						selectObject.pop_back();

					selectObject.push_back(object);
				}
			}
		}
	}
	else
	{
		for (int i = static_cast<int>(OBJECT_TYPE::GROUND_UNIT);
			i < static_cast<int>(OBJECT_TYPE::BACK_UI); ++i)
		{
			const vector<GameObject*>& groupObject
				= scene->GetGroupObject(static_cast<OBJECT_TYPE>(i));

			for (auto object : groupObject)
			{
				// AABB�浹�˻� 
				Transform* transform = object->GetComponent<Transform>();
				Vector2 position = transform->GetPosition();
				Vector2 scale = transform->GetScale();

				Vector2 objectMin = position - scale * 0.5f;
				Vector2 objectMax = position + scale * 0.5f;

				// �簢�� ���ο� ������
				if (minArea.x <= objectMax.x && maxArea.x >= objectMin.x
					&& minArea.y <= objectMax.y && maxArea.y >= objectMin.y)
				{
					selectObject.push_back(object);
				}
			}
		}
	}
	/// ���� �簢�� ���ο� ������Ʈ�� ������ ���� �δ븦 �״�� ���
	if (selectObject.empty())
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
		m_selectUnits = std::move(selectObject);
		
		// ���� ������ �δ뿡 �˸�
		for (auto object : m_selectUnits)
		{
			Unit* unit = object->GetComponent<Unit>();
			unit->SetSelct(true);
		}

	}

}
