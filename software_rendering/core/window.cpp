#include "window.h"
#include "keyboard.h"
#include "mouse.h"
#include "renderer.h"

Window::Window(LPCWSTR name_in, LPCWSTR className_in, int width_in, int height_in)
	:
	name(name_in),
	className(className_in),
	width(width_in),
	height(height_in),
	instance(GetModuleHandleW(nullptr))
{
	RegisterWindowClass();
	window = CreateWindowExW(NULL, className, name, WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, width, height, nullptr, nullptr, instance, nullptr);

	Mouse::RegisterRawInputDevice(window);

	renderer = std::make_unique<Renderer>(window, width, height);
}

Window::~Window()
{
	DestroyWindow(window);
	UnregisterClassW(className, instance);
}

void Window::DisplayWindow()
{
	ShowWindow(window, SW_SHOW);
}

void Window::HideWindow()
{
	ShowWindow(window, SW_HIDE);
}

bool Window::ProcessMessage()
{
	MSG msg = {};

	while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
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

void Window::UpdateInput()
{
	Keyboard::Update();
	Mouse::Update();
}

void Window::RegisterWindowClass()
{
	WNDCLASSEXW wc = {};

	wc.cbSize = sizeof(WNDCLASSEXA);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = instance;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpszClassName = className;

	RegisterClassExW(&wc);
}

LRESULT Window::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (Keyboard::HandleWM(hwnd, msg, wParam, lParam) || Mouse::HandleWM(hwnd, msg, wParam, lParam))
	{
		return DefWindowProcW(hwnd, msg, wParam, lParam);
	}

	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return S_OK;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}