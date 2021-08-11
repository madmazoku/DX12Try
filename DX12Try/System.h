#pragma once

#include "Config.h"

class System
{
private:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	static const LPCWSTR s_applicationName;
	static const LPCWSTR s_windowName;

public:
	System(Config& config);
	~System();

	bool Initialize();
	void Shutdown();
	void Run();

private:
	void Tick();
	LRESULT MessageHandler(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

	bool InitializeWindow();
	void ShutdownWindow();

private:
	Config& m_config;

	HINSTANCE m_hinstance;
	HWND m_hwnd;
};

