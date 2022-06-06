#include "pipeline.h"

Pipeline::Pipeline(int width, int height)
	:
	width(width),
	height(height)
{}

void Pipeline::Draw(Renderer& renderer)
{
	if (!vertexBuffer) assert(0 && "vertex buffer not bound");
	if (!indexBuffer) assert(0 && "index buffer not bound");
	if (!vertexShader) assert(0 && "vertex shader not bound");
	if (!pixelShader) assert(0 && "pixel shader not bound");

	VertexBuffer copy;
	for (auto& vertex : *vertexBuffer)
	{
		copy.push_back(vertexShader->Shade(vertex));

		copy.back().viewPosition /= copy.back().viewPosition.w;

		copy.back().viewPosition.x = (copy.back().viewPosition.x + 1.0f) * width * 0.5f;
		copy.back().viewPosition.y = (-copy.back().viewPosition.y + 1.0f) * height * 0.5f;
	}

	switch (primitiveTopology)
	{
	case PrimitiveTopology::ptLINELIST:
		for (size_t i = 0; i < indexBuffer->size(); i += 2)
		{
			rasterizer.DrawLine({ copy[(*indexBuffer)[i]], copy[(*indexBuffer)[i + 1]] }, pixelShader, renderer);
		}
		break;
	case PrimitiveTopology::ptTRIANGLELIST:
		for (size_t i = 0; i < indexBuffer->size(); i += 3)
		{
			rasterizer.DrawTriangle({ copy[(*indexBuffer)[i]], copy[(*indexBuffer)[i + 1]], copy[(*indexBuffer)[i + 2]] }, pixelShader, renderer);
		}
		break;
	}
}