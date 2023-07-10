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
	
	// 부대 이동 이벤트 발생
	if (input->IsKeyState(KEY::RMOUSE, KEY_STATE::TAP))
	{
		const SceneManager* sceneMgr = GetSceneManager();
		
		// 카메라 좌표계의 마우스 포지션
		Vector2 cameraMousePosition = input->GetCameraMousePosition();

		GameObject* effect1 = new GameObject("mouseEffect", GetManagerSet());
		effect1->CreateComponent<TextureRenderer>()->SetKey(L"MouseEffect1");
		effect1->CreateComponent<Transform>()->SetPosition(cameraMousePosition);
		effect1->Destory(0.1f);
		effect1->SetCameraAffected(false);
		sceneMgr->RegisterObject(effect1, OBJECT_TYPE::MOUSE_EFFECT);

		// 오브젝트에게 이동명령을 지시한다.

		Vector2 worldMousePostion = input->GetWorldMousePosition();

		for (auto object : m_selectUnits)
		{			Unit* unit = object->GetComponent<Unit>();
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

void Controller::GetUnits()
{
	/// 씬에서 오브젝트들을 받아온다 
	const SceneManager* sceneMgr = GetSceneManager();
	Scene* scene = sceneMgr->GetCurrentScene();

	const CameraManager* camera = GetCameraManager();
	// 카메라에서 월드 좌표계로 변환한다 
	Vector2 start = camera->CameraToWorld(m_dragStart);
	Vector2 end = camera->CameraToWorld(m_dragEnd);

	// 지정된 사각형의 Rect를 계산
	Vector2 minArea{}, maxArea{};
	minArea.x = FMath::Min(start.x, end.x);
	minArea.y = FMath::Min(start.y, end.y);
	maxArea.x = FMath::Max(start.x, end.x);
	maxArea.y = FMath::Max(start.y, end.y);

	// 차례대로 사각형내부에 있는지 판단한다
	vector<GameObject*> selectObject;

	// Area크기가 작으면 한개의 오브젝트만 선택한다
	if (maxArea.x - minArea.x <= 5.f && maxArea.y - minArea.y <= 5.f)
	{
		for (int i = static_cast<int>(OBJECT_TYPE::GROUND_UNIT);
			i < static_cast<int>(OBJECT_TYPE::BACK_UI); ++i)
		{
			const vector<GameObject*>& groupObject
				= scene->GetGroupObject(static_cast<OBJECT_TYPE>(i));

			for (auto object : groupObject)
			{
				// AABB충돌검사 
				Transform* transform = object->GetComponent<Transform>();
				Vector2 position = transform->GetPosition();
				Vector2 scale = transform->GetScale();

				Vector2 objectMin = position - scale * 0.5f;
				Vector2 objectMax = position + scale * 0.5f;

				// 사각형 내부에 있으면
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
				// AABB충돌검사 
				Transform* transform = object->GetComponent<Transform>();
				Vector2 position = transform->GetPosition();
				Vector2 scale = transform->GetScale();

				Vector2 objectMin = position - scale * 0.5f;
				Vector2 objectMax = position + scale * 0.5f;

				// 사각형 내부에 있으면
				if (minArea.x <= objectMax.x && maxArea.x >= objectMin.x
					&& minArea.y <= objectMax.y && maxArea.y >= objectMin.y)
				{
					selectObject.push_back(object);
				}
			}
		}
	}
	/// 만약 사각형 내부에 오브젝트가 없으면 원래 부대를 그대로 사용
	if (selectObject.empty())
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
		m_selectUnits = std::move(selectObject);
		
		// 새로 지정된 부대에 알림
		for (auto object : m_selectUnits)
		{
			Unit* unit = object->GetComponent<Unit>();
			unit->SetSelct(true);
		}

	}

}
