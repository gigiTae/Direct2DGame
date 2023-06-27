#include "GameProcessPCH.h"
#include "PathManager.h"

PathManager::PathManager():m_contentPath{}
{
}

PathManager::~PathManager()
{
}

void PathManager::Initalize()
{
	GetCurrentDirectoryW(255, m_contentPath);
	int iLen = (int)wcslen(m_contentPath);
	// 상위 폴더로
	for (int i = iLen - 1; 0 <= i; --i)
	{
		if ('\\' == m_contentPath[i])
		{
			m_contentPath[i] = '\0';
			break;
		}
	}

	//
}
