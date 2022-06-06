#pragma once
#include "window.h"
#include "pipeline.h"
#include "timer.h"
#include "vertex.h"

class TestVertexShader : public VertexShader
{
public:
	float distance = 3.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;

	virtual Vertex Shade(const Vertex& vertex) override
	{
		Matrix world = Matrix::Rotation({ pitch, yaw, 0.0f, 0.0f }) * Matrix::Translation({ 0.0f, 0.0f, distance, 0.0f });
		Matrix projection = Matrix::Perspective(1.777777f, 1.0f, 1.0f, 100.0f);

		Vertex transformed = vertex;
		transformed.worldPosition = vertex.worldPosition * world;
		transformed.viewPosition = vertex.worldPosition * world * projection;

		return transformed;
	}
};

class TestPixelShader : public PixelShader
{
public:
	virtual Vector Shade(const Vertex& vertex) override
	{
		return vertex.worldPosition;
	}
};

class Demo : public Window
{
private:
	Timer frameTimer;
	Pipeline pipeline;

	std::shared_ptr<VertexBuffer> cubeVB;
	std::shared_ptr<IndexBuffer> cubeIB;

	std::shared_ptr<TestVertexShader> vs;
	std::shared_ptr<TestPixelShader> ps;

public:
	Demo();

public:
	void Run();
};