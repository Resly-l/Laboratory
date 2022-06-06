#pragma once
#include <Windows.h>
#include <memory>

class Renderer;

class Window
{
private:
	HWND window;
	HINSTANCE instance;

	LPCWSTR name;
	LPCWSTR className;

	int width;
	int height;

protected:
	std::unique_ptr<Renderer> renderer;

public:
	Window(LPCWSTR name_in, LPCWSTR className_in, int width_in, int height_in);
	virtual ~Window();

public:
	void DisplayWindow();
	void HideWindow();
	bool ProcessMessage();
	void UpdateInput();

private:
	void RegisterWindowClass();
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};