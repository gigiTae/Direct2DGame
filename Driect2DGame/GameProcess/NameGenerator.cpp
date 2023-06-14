#include "GameProcessPCH.h"
#include "NameGenerator.h"

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
