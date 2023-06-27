#pragma once


/// <summary>
/// =����׿뵵=
/// ������Ʈ ���̹��� ���ִ� ���� Ŭ����
/// </summary>
class NameGenerator
{
public:
	static NameGenerator* GetInstance();
private:
	static NameGenerator* m_instance;

private:
	NameGenerator() = default;
	~NameGenerator();
public:
	const string GenerateName(const string& _name);

private:
	// �̸��������� �ʿ� ������ key : ������Ʈ �̸� value : ������Ʈ ���� Ƚ��
	map<const string, int> m_nameInfo;

};
