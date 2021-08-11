#include "Config.h"

Config::Config(int argc, char** argv) {
	m_currentDir = std::filesystem::current_path();
	m_appPath = argv[0];
	m_appDir = m_appPath.parent_path();

	InitializeWindowPlacement();
}

Config::~Config() {
}

void Config::InitializeWindowPlacement() {
	// Determine the resolution of the clients desktop screen.
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	RECT windowRect = { 0, 0, static_cast<LONG>(screenWidth >> 1), static_cast<LONG>(screenHeight >> 1) };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
	int wndWidth = static_cast<int>(windowRect.right - windowRect.left);
	int wndHeight = static_cast<int>(windowRect.bottom - windowRect.top);

	// Place the window in the middle of the screen.
	int wndPosX = (screenWidth - wndWidth) >> 1;
	int wndPosY = (screenHeight - wndHeight) >> 1;

	m_windowPos = { static_cast<LONG>(wndPosX), static_cast<LONG>(wndPosY) };
	m_windowSize = { static_cast<LONG>(wndWidth), static_cast<LONG>(wndHeight) };
}
