#pragma once
class PathManager
{
public:
	PathManager();
	~PathManager();

	void Initalize();
private:
	wchar_t m_contentPath[256];
};

