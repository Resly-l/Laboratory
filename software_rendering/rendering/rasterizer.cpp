#include "rasterizer.h"
#include <algorithm>

void Rasterizer::DrawLine(const Line& line, std::shared_ptr<PixelShader> pixelShader, Renderer& renderer)
{
	int xMax = (int)floorf(std::max(line.from.viewPosition.x, line.to.viewPosition.x) + 0.5f);
	int xMin = (int)floorf(std::min(line.from.viewPosition.x, line.to.viewPosition.x) + 0.5f);
	int xDistance = xMax - xMin;

	int yMax = (int)floorf(std::max(line.from.viewPosition.y, line.to.viewPosition.y) + 0.5f);
	int yMin = (int)floorf(std::min(line.from.viewPosition.y, line.to.viewPosition.y) + 0.5f);
	int yDistance = yMax - yMin;

	int dominantDistance = std::max(xDistance, yDistance);
	
	for (int i = 0; i <= dominantDistance; i++)
	{
		Vertex interpolated = line.from.GetInterpolated(line.to, (float)i / (float)dominantDistance);
		renderer.DrawPixel(interpolated.viewPosition, pixelShader->Shade(interpolated));
	}
}

void Rasterizer::DrawTriangle(const Triangle& triangle, std::shared_ptr<PixelShader> pixelShader, Renderer& renderer)
{
	std::vector<Vertex> vertices;
	vertices.push_back(triangle.v0);
	vertices.push_back(triangle.v1);
	vertices.push_back(triangle.v2);

	std::sort(vertices.begin(), vertices.end(),
		[](const Vertex& lhs, const Vertex& rhs)
		{
			return lhs.viewPosition.y < rhs.viewPosition.y;
		});

	Vertex top = vertices[0];
	Vertex mid = vertices[1];
	Vertex bottom = vertices[2];
	Vertex topToMid = mid - top;
	Vertex topToBottom = bottom - top;

	// y ratio of mid from top to bottom
	float alpha = (mid.viewPosition.y - top.viewPosition.y) / topToBottom.viewPosition.y;

	Vertex newMid = top.GetInterpolated(bottom, alpha);

	if (newMid.viewPosition.x > mid.viewPosition.x)
	{
		std::swap(newMid, mid);
	}

	DrawFlatTopTriangle(newMid, mid, bottom, pixelShader, renderer);
	DrawFlatBottomTriangle(top, newMid, mid, pixelShader, renderer);
}

void Rasterizer::DrawFlatTopTriangle(const Vertex& topLeft, const Vertex& topRight, const Vertex& bottom, std::shared_ptr<PixelShader> pixelShader, Renderer& renderer)
{
	float height = bottom.viewPosition.y - topLeft.viewPosition.y;
	for (int y = (int)floorf(topLeft.viewPosition.y + 0.5f); y <= (int)floorf(bottom.viewPosition.y + 0.5f); y++)
	{
		Vertex from = topLeft.GetInterpolated(bottom, (y - topLeft.viewPosition.y) / height);
		Vertex to = topRight.GetInterpolated(bottom, (y - topRight.viewPosition.y) / height);
		DrawScanLine(from, to, pixelShader, renderer);
	}
}

void Rasterizer::DrawFlatBottomTriangle(const Vertex& top, const Vertex& bottomLeft, const Vertex& bottomRight, std::shared_ptr<PixelShader> pixelShader, Renderer& renderer)
{
	float height = bottomLeft.viewPosition.y - top.viewPosition.y;
	for (int y = (int)floorf(top.viewPosition.y + 0.5f); y <= (int)floorf(bottomLeft.viewPosition.y + 0.5f); y++)
	{
		Vertex from = top.GetInterpolated(bottomLeft, (y - top.viewPosition.y) / height);
		Vertex to = top.GetInterpolated(bottomRight, (y - top.viewPosition.y) / height);
		DrawScanLine(from, to, pixelShader, renderer);
	}
}

void Rasterizer::DrawScanLine(const Vertex& from, const Vertex& to, std::shared_ptr<PixelShader> pixelShader, Renderer& renderer)
{
	float width = to.viewPosition.x - from.viewPosition.x;
	for (int x = (int)floorf(from.viewPosition.x); x <= (int)floorf(to.viewPosition.x); x++)
	{
		Vertex interpolated = from.GetInterpolated(to, (x - from.viewPosition.x) / width);
		renderer.DrawPixel(interpolated.viewPosition, pixelShader->Shade(interpolated));
	}
}