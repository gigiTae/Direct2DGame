#pragma once


/// <summary>
/// =디버그용도=
/// 오브젝트 네이밍을 해주는 전역 클래스
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
	// 이름정보들을 맵에 저장함 key : 오브젝트 이름 value : 오브젝트 생성 횟수
	map<const wstring, int> m_nameInfo;
};
