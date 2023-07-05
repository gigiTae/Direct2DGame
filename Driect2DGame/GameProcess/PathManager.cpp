#include "GameProcessPCH.h"
#include "PathManager.h"


wchar_t PathManager::m_relativePath[256] = {};

PathManager::PathManager()
{
}

PathManager::~PathManager()
{
}

void PathManager::Initalize()
{
	GetCurrentDirectoryW(255, PathManager::m_relativePath);
	int iLen = (int)wcslen(PathManager::m_relativePath);
	// 상위 폴더로
	for (int i = iLen - 1; 0 <= i; --i)
	{
		if ('\\' == PathManager::m_relativePath[i])
		{
			PathManager::m_relativePath[i] = '\0';
			break;
		}
	}
}

const wchar_t* PathManager::GetRelativPath()
{
	assert(m_relativePath[0] != L'\0'
	|| !L"초기화하지 않았습니다");

	return m_relativePath;
}
