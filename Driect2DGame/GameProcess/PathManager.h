#pragma once


/// <summary>
/// ���� ��θ� �޾ƿ��� �Ŵ��� 
/// static�� ����ϱ� �ߴµ� 
/// ���� �޸𸮰����� ��ü�� �Ҵ��ؾ��ұ�?
/// �𸣰ڴ�....
/// </summary>
class PathManager
{
public:
	PathManager();
	~PathManager();

	void Initalize();

	static const wchar_t* GetRelativPath() { return m_relativePath; }

private:
	static wchar_t m_relativePath[256];
};

