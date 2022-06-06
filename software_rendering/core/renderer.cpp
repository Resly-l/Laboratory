#include "renderer.h"

Renderer::Renderer(HWND window, int width_in, int height_in)
	:
	width(width_in),
	height(height_in),
	backBuffer(width_in * height_in)
{
	mainDC = GetDC(window);
	bufferDC = CreateCompatibleDC(mainDC);
}

void Renderer::PresentBuffer()
{
	auto bitmap = CreateBitmap(width, height, 1, sizeof(unsigned int) * 8, backBuffer.data());
	memset(backBuffer.data(), 0, backBuffer.size() * sizeof(backBuffer[0]));

	SelectObject(bufferDC, bitmap);
	BitBlt(mainDC, 0, 0, width, height, bufferDC, 0, 0, SRCCOPY);

	DeleteObject(bitmap);
}

void Renderer::DrawPixel(int x, int y, const Vector& color)
{
	if (int index = y * (int)width + x - 1; index >= 0 && index < width * height)
	{
		backBuffer[index] = RGB(color.z * 255.0f, color.y * 255.0f, color.x * 255.0f);
	}
}

void Renderer::DrawPixel(const Vector& point, const Vector& color)
{
	DrawPixel((int)floorf(point.x + 0.5f), (int)floorf(point.y + 0.5f), color);
}