#include "GameProcessPCH.h"
#include "NameGenerator.h"

NameGenerator::~NameGenerator()
{
}

const wstring NameGenerator::GenerateName(const wstring& _name)
{
	auto iter = m_nameInfo.find(_name);

	// 처음으로 생성된 이름
	if (iter == m_nameInfo.end())
	{
		m_nameInfo.insert(std::make_pair(_name, 1));
		return _name;
	}

	// 이미 생성한적 있는 이름이면 숫자를 붙여서 생성한다.
	int number = iter->second++;
	const wstring name = _name + std::to_wstring(number);

	return name;
}
