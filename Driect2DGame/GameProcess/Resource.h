#pragma once

/// <summary>
/// ���ҽ� �������̽�
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
	wstring m_key; // ���ҽ� Ű
	wstring m_relativePath; // ���ҽ� �����

};

