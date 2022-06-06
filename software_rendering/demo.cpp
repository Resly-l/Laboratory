#include "demo.h"
#include "core/renderer.h"
#include "core/keyboard.h"

Demo::Demo()
	:
	Window(L"Software Rendering", L"Window Class", 1600, 900),
	pipeline(1600, 900)
{
	Window::DisplayWindow();

	cubeVB = std::make_shared<VertexBuffer>();
	cubeIB = std::make_shared<IndexBuffer>();

	vs = std::make_shared<TestVertexShader>();
	ps = std::make_shared<TestPixelShader>();

	cubeVB->push_back({ { -0.5f, 0.5f, -0.5f, 1.0f } });
	cubeVB->push_back({ { 0.5f, 0.5f, -0.5f, 1.0f } });
	cubeVB->push_back({ { 0.5f, -0.5f, -0.5f, 1.0f } });
	cubeVB->push_back({ { -0.5f, -0.5f, -0.5f, 1.0f } });

	cubeVB->push_back({ { -0.5f, 0.5f, 0.5f, 1.0f } });
	cubeVB->push_back({ { 0.5f, 0.5f, 0.5f, 1.0f } });
	cubeVB->push_back({ { 0.5f, -0.5f, 0.5f, 1.0f } });
	cubeVB->push_back({ { -0.5f, -0.5f, 0.5f, 1.0f } });

	cubeIB->push_back(0);
	cubeIB->push_back(1);
	cubeIB->push_back(1);
	cubeIB->push_back(2);
	cubeIB->push_back(2);
	cubeIB->push_back(3);
	cubeIB->push_back(3);
	cubeIB->push_back(0);

	cubeIB->push_back(4);
	cubeIB->push_back(5);
	cubeIB->push_back(5);
	cubeIB->push_back(6);
	cubeIB->push_back(6);
	cubeIB->push_back(7);
	cubeIB->push_back(7);
	cubeIB->push_back(4);

	cubeIB->push_back(0);
	cubeIB->push_back(4);
	cubeIB->push_back(1);
	cubeIB->push_back(5);
	cubeIB->push_back(2);
	cubeIB->push_back(6);
	cubeIB->push_back(3);
	cubeIB->push_back(7);

	pipeline.SetPrimitiveTopology(PrimitiveTopology::ptLINELIST);
	pipeline.SetVertexBuffer(cubeVB);
	pipeline.SetIndexBuffer(cubeIB);
	pipeline.SetVertexShader(vs);
	pipeline.SetPixelShader(ps);
}

void Demo::Run()
{
	while (Window::ProcessMessage())
	{
		Window::UpdateInput();
			
		const float deltaSeconds = (float)frameTimer.Mark();

		if (Keyboard::IsKeyHold('R'))
			vs->distance += deltaSeconds;
		if (Keyboard::IsKeyHold('F'))
			vs->distance -= deltaSeconds;

		if (Keyboard::IsKeyHold('W'))
			vs->pitch += deltaSeconds;
		if (Keyboard::IsKeyHold('S'))
			vs->pitch -= deltaSeconds;
		if (Keyboard::IsKeyHold('A'))
			vs->yaw += deltaSeconds;
		if (Keyboard::IsKeyHold('D'))
			vs->yaw -= deltaSeconds;

		pipeline.Draw(*renderer);

		renderer->PresentBuffer();
	}
}