#include "GameProcessPCH.h"
#include "NameGenerator.h"

// ������� ���� �ʱ�ȭ 
NameGenerator* NameGenerator::m_instance = nullptr;

NameGenerator* NameGenerator::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new NameGenerator();
	}
	return m_instance;
}

NameGenerator::~NameGenerator()
{
}

const wstring NameGenerator::GenerateName(const wstring& _name)
{
	auto iter = m_nameInfo.find(_name);

	// ó������ ������ �̸�
	if (iter == m_nameInfo.end())
	{
		m_nameInfo.insert(std::make_pair(_name, 1));
		return _name;
	}

	// �̹� �������� �ִ� �̸��̸� ���ڸ� �ٿ��� �����Ѵ�.
	int number = iter->second++;
	const wstring name = _name + std::to_wstring(number);

	return name;
}
