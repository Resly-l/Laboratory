#include "demo.h"
#include "renderer.h"

Demo::Demo()
	:
	Window(L"demo", 1600, 900)
{

}

void Demo::Run()
{
	while (Window::ProcessMessage())
	{
		renderer->BeginFrame();
		renderer->EndFrame();
	}
}