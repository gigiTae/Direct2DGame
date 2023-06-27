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

const string NameGenerator::GenerateName(const string& _name)
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
	const string name = _name + std::to_string(number);

	return name;
}
