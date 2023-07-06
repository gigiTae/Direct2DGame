#include "GameProcessPCH.h"
#include "Animator.h"
#include "Animation.h"

Animator::Animator()
	:Component(CALL_ORDER::ANIMATOR, typeid(this).name())
	, m_animations{}
	, m_currentAnimation(nullptr)
	, m_repeat(false)
{}

Animator::~Animator()
{
	//  모든 애니메이션 삭제
	for (auto& iter : m_animations)
	{
		if (iter.second != nullptr)
		{
			delete iter.second;
		}
	}
}

void Animator::CreateAnimation(const wstring& _name
	, const wstring& _textureKey
	, Vector2 _startLeftTop, Vector2 _sliceSize
	, Vector2 _step, float _duration, UINT _frameCount)
{
	Animation* animation = FindAnimation(_name);
	assert(nullptr == animation);

	// 애니메이션 생성
	animation = new Animation();
	animation->SetAnimator(this);
	animation->Create(_name, _textureKey, _startLeftTop
		, _sliceSize, _step, _duration, _frameCount);

	// 애니메이션 저장
	m_animations.insert(make_pair(_name, animation));
}

Animation* Animator::FindAnimation(const wstring& _name)
{
	auto iter = m_animations.find(_name);

	if (iter != m_animations.end())
	{
		return iter->second;
	}

	return nullptr;
}

void Animator::Play(const wstring& _name, bool _repeat)
{
	m_currentAnimation = FindAnimation(_name);
	m_repeat = _repeat;
}

void Animator::LateUpdate(float _deltaTime, const InputManager* _inputManager)
{
	if (nullptr != m_currentAnimation)
	{
		m_currentAnimation->Update(_deltaTime);

		// 반복재생인 경우 다시 재생
		if (m_repeat && m_currentAnimation->IsFinish())
		{
			m_currentAnimation->SetFrame(0);
		}
	}
}

void Animator::Render(D2DRenderer* _d2DRenderer)
{
	if (nullptr != m_currentAnimation)
	{
		m_currentAnimation->Render(_d2DRenderer);
	}
}
