#include <iostream>
#include "entity.h"
#include "system.h"
#include "ecs_factory.h"

class TestComponent : public Component<TestComponent>
{
public:
	void func()
	{
		std::cout << "function of TestComponent" << std::endl;
	}
};

class TestComponent2 : public Component<TestComponent2> {};

class TestSystem : public System<TestSystem>
{
public:
	void Update() override
	{
		
	}
};

int main()
{
	ECSFactory factory;
	Entity entity;

	factory.AddComponentSet<TestComponent>();

	auto comp = entity.AddComponent<TestComponent>(factory);
	comp->func();

	return 0;
}