#include "renderer.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

Renderer::Renderer(HWND hWnd, int width, int height)
	:
	width(width),
	height(height)
{
	CreateDeviceAndContext();
	CreateSwapChain(hWnd);
	CreateBackbuffer();
	SetViewport();
}

void Renderer::BeginFrame()
{
	float clearColor[4] = {};
	deviceContext->ClearRenderTargetView(backBuffer.Get(), clearColor);
}

void Renderer::EndFrame()
{
	swapChain->Present(0, 0);
}

void Renderer::CreateDeviceAndContext()
{
	unsigned int flags = 0;

#ifdef _DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags, nullptr, 0, D3D11_SDK_VERSION, &device, {}, &deviceContext)))
	{
		MessageBox(nullptr, L"failed to create graphics device", L"Renderer Exception", MB_ICONERROR | MB_OK);
		PostQuitMessage(0);
	}
}

void Renderer::CreateSwapChain(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;

	Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice;
	if (FAILED(device->QueryInterface(__uuidof(IDXGIDevice), &dxgiDevice)))
	{
		MessageBox(nullptr, L"failed to query dxgi device", L"Renderer Exception", MB_ICONERROR | MB_OK);
		PostQuitMessage(0);
		return;
	}

	Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
	if (FAILED(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), &dxgiAdapter)))
	{
		MessageBox(nullptr, L"failed to get dxgi adapter", L"Renderer Exception", MB_ICONERROR | MB_OK);
		PostQuitMessage(0);
		return;
	}

	Microsoft::WRL::ComPtr<IDXGIFactory> dxgiFactory;
	if (FAILED(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), &dxgiFactory)))
	{
		MessageBox(nullptr, L"failed to get dxgi factory", L"Renderer Exception", MB_ICONERROR | MB_OK);
		PostQuitMessage(0);
		return;
	}

	if (FAILED(dxgiFactory->CreateSwapChain(device.Get(), &sd, &swapChain)))
	{
		MessageBox(nullptr, L"failed to create swap chain", L"Renderer Exception", MB_ICONERROR | MB_OK);
		PostQuitMessage(0);
		return;
	}

	dxgiFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER);
}

void Renderer::CreateBackbuffer()
{
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	swapChain->GetBuffer(0u, __uuidof(ID3D11Resource), &resource);

	if (FAILED(device->CreateRenderTargetView(resource.Get(), nullptr, &backBuffer)))
	{
		MessageBox(nullptr, L"failed to create backbuffer", L"Renderer Exception", MB_ICONERROR | MB_OK);
		PostQuitMessage(0);
		return;
	}

	deviceContext->OMSetRenderTargets(1u, backBuffer.GetAddressOf(), nullptr);
}

void Renderer::SetViewport()
{
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	deviceContext->RSSetViewports(1, &viewport);
}