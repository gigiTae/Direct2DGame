#pragma once

class Animator;

struct Frame
{
	Vector2 leftTop; // �»�� ��ǥ
	Vector2 slice; 
	Vector2 offset;
	float duration;
};


/// <summary>
/// �ִϸ��̼� ������ �����ϴ� Ŭ�����̴�
/// 
/// Animation�� ���� Animator�� �������� ����� ��������
/// 
/// </summary>
class Animation
{
public:
	Animation();
	~Animation();

public:
	bool IsFinish() { return m_finish; }
	void SetFrame(int _index)
	{
		m_finish = false;
		m_currentFrame = _index;
		m_elapsedTime = 0.f;
	}

	Frame& GetFrame(int _index) { return m_frames[_index]; }
	size_t GetMaxFrame() { return m_frames.size(); }

public:
	void Update(float _deltaTime);
	void Render(D2DRenderer* _d2DRenderer);
	void SetAnimator(Animator* _animator) { m_animator = _animator; }

	// �ִϸ��̼� ���� ����
	void Create(const wstring& _name, const wstring& _textureKey, Vector2 _leftTop
		, Vector2 _sliceSize, Vector2 _step, float _duration, UINT _frameCount);

public:
	const wstring& GetName() {return m_name;}

private:
	wstring m_name; // �ִϸ��̼� �̸�
	wstring m_textureKey; // �ؽ�ó Ű��
	Animator* m_animator; // �ִϸ��̼��� �����ϰ� �ִ� �ִϸ�����
	vector<Frame> m_frames; // ��� ������ ����
	int m_currentFrame; // ���� ������ �ε���
	float m_elapsedTime; 
	bool m_finish; // ����� ������
};

