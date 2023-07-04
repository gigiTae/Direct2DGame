#include "GameProcessPCH.h"
#include "FileManager.h"

void FileManager::GetFileMemberPath(vector<wstring>& _files, const wstring& _filePath, bool _allDirectories)
{
	wstring tmp = _filePath + wstring(L"\\*.*");
	WIN32_FIND_DATA fd;

	HANDLE hFind = FindFirstFile(tmp.c_str(), &fd);

	if (INVALID_HANDLE_VALUE != hFind)
	{
		do {
			if (fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				if (_allDirectories)
				{
					if (fd.cFileName[0] != '.')
					{
						tmp = _filePath + wstring(L"\\") + wstring(fd.cFileName);
						GetFileMemberPath(_files, tmp, _allDirectories);
					}
				}
			}
			else
			{
				tmp = _filePath + wstring(L"\\") + wstring(fd.cFileName);
				_files.push_back(tmp);
			}
		} while (FindNextFile(hFind, &fd));
		FindClose(hFind);
	}
}

void FileManager::GerFileMemberName(vector<wstring>& _files, const wstring& _filePath, bool _allDirectories)
{
	wstring tmp = _filePath + wstring(L"\\*.*");
	WIN32_FIND_DATA fd;

	HANDLE hFind = FindFirstFile(tmp.c_str(), &fd);

	if (INVALID_HANDLE_VALUE != hFind)
	{
		do {
			if (fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				if (_allDirectories)
				{
					if (fd.cFileName[0] != '.')
					{
						tmp = _filePath + wstring(L"\\") + wstring(fd.cFileName);
						GetFileMemberPath(_files, tmp, _allDirectories);
					}
				}
			}
			else
			{
				tmp = wstring(fd.cFileName);
				_files.push_back(tmp);
			}
		} while (FindNextFile(hFind, &fd));
		FindClose(hFind);
	}
}
