#include "window.h"
#include "renderer.h"

Window::Window(const std::wstring& name, int width, int height)
	:
	hInstance(GetModuleHandle(nullptr)),
	name(name),
	className(L"window class"),
	width(width),
	height(height)
{
	RegisterWindowClass();

	hWnd = CreateWindowEx(NULL, className.c_str(), name.c_str(), WS_SYSMENU | WS_MINIMIZEBOX, 
		int(GetSystemMetrics(SM_CXSCREEN) * 0.5f - width * 0.5f), int(GetSystemMetrics(SM_CYSCREEN) * 0.5f - height * 0.5f), width, height,
		nullptr, nullptr, hInstance, nullptr
	);

	if (hWnd == nullptr)
	{
		MessageBox(nullptr, L"failed to create window", L"Window Exception", MB_ICONERROR | MB_OK);
		PostQuitMessage(0);
		return;
	}

	ShowWindow(hWnd, SW_SHOW);

	renderer = std::make_unique<Renderer>(hWnd, width, height);
}

Window::~Window()
{
	DestroyWindow(hWnd);
	UnregisterClassW(className.c_str(), hInstance);
}

bool Window::ProcessMessage()
{
	MSG msg = {};

	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;
		}

		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return true;
}

void Window::RegisterWindowClass()
{
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	//wc.hIcon = (HICON)LoadImage(0, nullptr, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpszClassName = className.c_str();

	RegisterClassEx(&wc);
}

LRESULT Window::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return S_OK;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}