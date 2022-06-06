#pragma once
#include <vector>
#include <memory>
#include "rasterizer.h"

enum class PrimitiveTopology
{
	ptLINELIST,
	ptTRIANGLELIST
};

class Pipeline
{
private:
	PrimitiveTopology primitiveTopology;
	std::shared_ptr<VertexBuffer> vertexBuffer;
	std::shared_ptr<IndexBuffer> indexBuffer;
	std::shared_ptr<VertexShader> vertexShader;
	std::shared_ptr<PixelShader> pixelShader;
	Rasterizer rasterizer;

	int width;
	int height;

public:
	Pipeline(int width, int height);

public:
	void SetPrimitiveTopology(PrimitiveTopology pt) { primitiveTopology = pt; }
	void SetVertexBuffer(std::shared_ptr<VertexBuffer> vb) { vertexBuffer = vb; }
	void SetIndexBuffer(std::shared_ptr<IndexBuffer> ib) { indexBuffer = ib; }
	void SetVertexShader(std::shared_ptr<VertexShader> vs) { vertexShader = vs; }
	void SetPixelShader(std::shared_ptr<PixelShader> ps) { pixelShader = ps; }

	void Draw(Renderer& renderer);
};