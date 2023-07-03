#pragma once

/// <summary>
/// 리소스 인터페이스
/// </summary>
class Resource abstract
{
public:
	Resource() = default;
	~Resource();

public:
	void SetKey(const wstring& _key) { m_key = _key; }
	void SetRelativePath(const wstring& _path) { m_relativePath = _path; }

	const wstring& GetKey() { return m_key; }
	const wstring& GetRelativePath() { return  m_relativePath; }

private:
	wstring m_key; // 리소스 키
	wstring m_relativePath; // 리소스 상대경로

};

