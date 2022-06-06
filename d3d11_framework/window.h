#pragma once
#include "light_windows.h"
#include <string>
#include <memory>

class Window
{
private:
	HWND hWnd;
	HINSTANCE hInstance;

	std::wstring name;
	std::wstring className;

	int width;
	int height;

protected:
	std::unique_ptr<class Renderer> renderer;

public:
	Window(const std::wstring& name, int width, int height);
	virtual ~Window();

public:
	// returns true after processing all messages
	// returns false after WM_QUIT message
	bool ProcessMessage();

private:
	void RegisterWindowClass();
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};