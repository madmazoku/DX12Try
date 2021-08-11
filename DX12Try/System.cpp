#include "Utils.h"

#include "System.h"

const LPCWSTR System::s_applicationName = L"DX12TryClass";
const LPCWSTR System::s_windowName = L"DX12Try";

LRESULT CALLBACK System::WndProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	//LOG << std::hex << "hwnd: " << hwnd << "; umsg: " << uMessage << "; wp: " << wParam << "; lp: " << lParam << std::dec << std::endl;
	System* pSystem = reinterpret_cast<System*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	switch (uMessage)
	{
	case WM_CREATE:
	{
		LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
		return 0;
	}

	// Check if the window is being destroyed.
	case WM_DESTROY:
	{
		LOG << "Destroy window" << std::endl;
		PostQuitMessage(0);
		return 0;
	}

	}

	if (pSystem != 0)
		return pSystem->MessageHandler(hwnd, uMessage, wParam, lParam);
	else
		return DefWindowProc(hwnd, uMessage, wParam, lParam);
}

System::System(Config& config) : m_config(config), m_hinstance((HINSTANCE)INVALID_HANDLE_VALUE), m_hwnd((HWND)INVALID_HANDLE_VALUE) {

}

System::~System() {

}

bool System::Initialize() {

	if (!InitializeWindow())
		return false;

	return true;
}

void System::Shutdown() {
	ShutdownWindow();
}

void System::Run() {
	MSG msg;

	ZeroMemory(&msg, sizeof(MSG));

	// Loop until there is a quit message from the window or the user.
	while (true)
	{
		// Handle the windows messages.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			Tick();
		}

		if (msg.message == WM_QUIT)
			break;
	}
}

bool System::InitializeWindow() {
	m_hinstance = GetModuleHandle(NULL);
	if (m_hinstance == (HINSTANCE)INVALID_HANDLE_VALUE) {
		LOG << "Invalid module handle" << std::endl;
		return false;
	}

	WNDCLASSEX wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = s_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	if (!RegisterClassEx(&wc)) {
		LOG << "Can't register window class";
		return false;
	}

	POINT windowPos = m_config.GetWindowPos();
	SIZE windowSize = m_config.GetWindowSize();

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(
		0, 
		s_applicationName, 
		s_windowName, 
		WS_OVERLAPPEDWINDOW, 
		windowPos.x, 
		windowPos.y, 
		windowSize.cx, 
		windowSize.cy, 
		NULL, 
		NULL, 
		m_hinstance, 
		(LPVOID)this
	);
	if (m_hwnd == NULL) {
		DWORD dwError = GetLastError();
		LOG << "Can't create window: " << LAST_ERROR_MSG(dwError) << std::endl;
		return false;
	}

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	return true;
}

void System::ShutdownWindow() {
	if (m_hwnd == (HWND)INVALID_HANDLE_VALUE)
		return;

	DestroyWindow(m_hwnd);
	m_hwnd = (HWND)INVALID_HANDLE_VALUE;

	UnregisterClass(s_applicationName, m_hinstance);
	m_hinstance = (HINSTANCE)INVALID_HANDLE_VALUE;
}

void System::Tick() {

}

LRESULT System::MessageHandler(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMessage, wParam, lParam);
}