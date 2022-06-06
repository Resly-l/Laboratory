#pragma once
#include <unordered_map>
#include <memory>
#include <vector>
#include "component.h"
#include "ecs_factory.h"

class Entity
{
private:
	Entity* parent = nullptr;
	std::vector<std::unique_ptr<Entity>> children;

	std::unordered_map<ComponentID, ComponentBase*> components;

public:
	virtual ~Entity() = default;

public:
	Entity* AddChild()
	{
		children.push_back(std::make_unique<Entity>());
		return children.back().get();
	}

	std::vector<std::unique_ptr<Entity>>& GetChildren()
	{
		return children;
	}

	template <typename ComponentType>
	ComponentType* AddComponent(ECSFactory& factory)
	{
		if (auto component = factory.AddComponent<ComponentType>())
		{
			components[ComponentType::id] = component;
			return component;
		}
		return nullptr;
	}
};