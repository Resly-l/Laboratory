#pragma once
#include "light_windows.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>

class Renderer
{
private:
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> backBuffer;

	int width;
	int height;

public:
	Renderer(HWND hWnd, int width, int height);

public:
	int GetWidth() { return width; }
	int GetHeight() { return height; }

	void BeginFrame();
	void EndFrame();

private:
	void CreateDeviceAndContext();
	void CreateSwapChain(HWND hWnd);
	void CreateBackbuffer();
	void SetViewport();
};