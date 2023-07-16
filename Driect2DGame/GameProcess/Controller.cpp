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
	
	// 사각형 그리기
	if (m_isDragging)
		_d2DRenderer->DrawRectangle(m_dragStart, m_dragEnd, D2D1::ColorF::Green);
	// 마우스위치에 오브젝트가 있으면 표시
	else if (m_onMouseUnit)
	{
		const CameraManager* camera = GetCameraManager();
		Vector2 cameraMousePosition = camera->WorldToCamera(m_currentMousePosition);

		_d2DRenderer->DrawBitMap(L"OnMouseEffect", cameraMousePosition);
	}

}

void Controller::Update(float _deltaTime)
{
	// 삭제 예정인 오브젝트 처리
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
	// 선택된 부대에게 명령내리기
	OrderSelectUnits();
}

void Controller::OnMouseDown()
{
	/// 처음으로 부대지정 시작
	const InputManager* input = GetInputManager();
	Vector2 mouse = input->GetCameraMousePosition();

	m_isDragging = true;
	m_dragStart = mouse;
}

void Controller::OnMouse()
{
	/// 사각형 꼭지점 
	const InputManager* input = GetInputManager();
	Vector2 mouse = input->GetCameraMousePosition();

	m_dragEnd = mouse;
}

void Controller::OnMouseUp()
{
	m_isDragging = false;
	
	/// 부대 지정 함수 추가
	GetUnits();
}

void Controller::OrderSelectUnits()
{
	const InputManager* input = GetInputManager();


	// 부대 이동 이벤트 발생
	if (input->IsKeyState(KEY::RMOUSE, KEY_STATE::TAP))
	{
		const SceneManager* sceneMgr = GetSceneManager();

		// 카메라 좌표계의 마우스 포지션
		Vector2 cameraMousePosition = input->GetCameraMousePosition();

		GameObject* effect1 = new GameObject("mouseEffect", GetManagerSet(), OBJECT_TYPE::MOUSE_EFFECT);
		effect1->CreateComponent<TextureRenderer>()->SetKey(L"MouseEffect1");
		effect1->CreateComponent<Transform>()->SetPosition(cameraMousePosition);
		effect1->Destory(0.15f);
		effect1->SetCameraAffected(false);
		sceneMgr->RegisterObject(effect1);

		// 오브젝트에게 이동명령을 지시한다.

		Vector2 worldMousePostion = input->GetWorldMousePosition();

		for (auto object : m_selectUnits)
		{
			Unit* unit = object->GetComponent<Unit>();
			unit->MoveUnit(worldMousePostion);
		}
	}
	else if (input->IsKeyState(KEY::H, KEY_STATE::HOLD))
	{
		// 지정된 부대에게 정지 명령을 지시한다.
		for (auto object : m_selectUnits)
		{
			Unit* unit = object->GetComponent<Unit>();
			unit->HoldUnit();
		}
	}
	else if (input->IsKeyState(KEY::A, KEY_STATE::TAP) && m_onMouseUnit)
	{
		// 지정된 부대에게 정지 명령을 지시한다.
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

	// 앞쪽배열의 오브젝트를 가져온다.
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
	// 카메라에서 월드 좌표계로 변환한다 
	Vector2 start = camera->CameraToWorld(m_dragStart);
	Vector2 end = camera->CameraToWorld(m_dragEnd);

	const CollisionManager* collisionMgr = GetCollisionManager();

	// 지정된 사각형의 Rect를 계산
	Vector2 minArea{}, maxArea{};
	minArea.x = FMath::Min(start.x, end.x);
	minArea.y = FMath::Min(start.y, end.y);
	maxArea.x = FMath::Max(start.x, end.x);
	maxArea.y = FMath::Max(start.y, end.y);

	// 차례대로 사각형내부에 있는지 판단한다
	vector<Collider*> selectColliders{};

	// 사각형의 크기가 작은 경우 한개의 오브젝트만 선택한다
	if ((maxArea - minArea).LengthSquared() < 32.f && m_onMouseUnit != nullptr)
	{
		selectColliders.push_back(m_onMouseUnit->GetComponent<Collider>());
	}
	else
	{
		collisionMgr->DetectBoxToCollider(minArea, maxArea, selectColliders);

		// 원형 콜라이더는 배열에서 제거한다.
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

	// 만약 사각형 내부에 오브젝트가 없으면 원래 부대를 그대로 사용
	if (selectColliders.empty())
	{
		return;
	}
	else
	{
		// 원래 부대는 지정해제 처리
		for (auto object : m_selectUnits)
		{
			Unit* unit = object->GetComponent<Unit>();
			unit->SetSelct(false);
		}

		// 새로지정된 부대로 설정
		m_selectUnits.clear();

		for (auto collider : selectColliders)
		{
			m_selectUnits.push_back(collider->GetGameObject());
		}
		
		// 새로 지정된 부대에 알림
		for (auto object : m_selectUnits)
		{
			Unit* unit = object->GetComponent<Unit>();
			unit->SetSelct(true);
		}

	}

}
