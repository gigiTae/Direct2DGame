#pragma once


/// <summary>
/// =����׿뵵=
/// ������Ʈ ���̹��� ���ִ� ���� Ŭ����
/// </summary>
class NameGenerator
{
public:
	static NameGenerator& GetInstance() { static NameGenerator nameGenerator; return nameGenerator; }

private:
	NameGenerator() = default;
	~NameGenerator();
public:
	const wstring GenerateName(const wstring& _name);
	
private:
	// �̸��������� �ʿ� ������ key : ������Ʈ �̸� value : ������Ʈ ���� Ƚ��
	map<const wstring, int> m_nameInfo;
};
