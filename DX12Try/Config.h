#pragma once

#include <ostream>
#include <filesystem>
#include <Windows.h>

class Config
{
public:
	Config(int argc, char** argv);
	~Config();

	POINT GetWindowPos() { return m_windowPos; }
	SIZE GetWindowSize() { return m_windowSize; }

private:
	std::filesystem::path m_currentDir;
	std::filesystem::path m_appPath;
	std::filesystem::path m_appDir;

	POINT m_windowPos;
	SIZE m_windowSize;

	void InitializeWindowPlacement();
};
