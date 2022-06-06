#pragma once
#include <memory>
#include "math.h"
#include "shader.h"
#include "renderer.h"

class Rasterizer
{
public:
	static void DrawLine(const Line& line, std::shared_ptr<PixelShader> pixelShader, Renderer& renderer);
	static void DrawTriangle(const Triangle& triangle, std::shared_ptr<PixelShader> pixelShader, Renderer& renderer);
	
private:
	static void DrawFlatTopTriangle(const Vertex& topLeft, const Vertex& topRight, const Vertex& bottom, std::shared_ptr<PixelShader> pixelShader, Renderer& renderer);
	static void DrawFlatBottomTriangle(const Vertex& top, const Vertex& bottomLeft, const Vertex& bottomRight, std::shared_ptr<PixelShader> pixelShader, Renderer& renderer);
	static void DrawScanLine(const Vertex& from, const Vertex& to, std::shared_ptr<PixelShader> pixelShader, Renderer& renderer);
};