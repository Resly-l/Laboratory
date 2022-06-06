#pragma once
#include <Windows.h>
#include <vector>
#include "mathematics.h"

class Renderer
{
private:
	HDC mainDC;
	HDC bufferDC;
	std::vector<unsigned int> backBuffer;

	int width;
	int height;

public:
	Renderer(HWND window, int width_in, int height_in);

public:
	void PresentBuffer();
	void DrawPixel(int x, int y, const Vector& color);
	void DrawPixel(const Vector& point, const Vector& color);
};