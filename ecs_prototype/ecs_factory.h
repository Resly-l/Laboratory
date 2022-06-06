#pragma once
#include <unordered_map>
#include <array>
#include <memory>
#include "component.h"

class BaseComponentSet
{
public:
	static constexpr size_t numMaxComponents = 2048;

public:
	virtual ~BaseComponentSet() = default;
};

template <typename ComponentType>
class ComponentSet : public BaseComponentSet
{
public:
	std::array<ComponentType, numMaxComponents> components;
};

class ECSFactory
{
private:
	std::unordered_map<ComponentID, std::unique_ptr<BaseComponentSet>> componentSets;

public:
	template <typename ComponentType>
	void AddComponentSet()
	{
		if (componentSets.find(ComponentType::id) == componentSets.end())
		{
			componentSets[ComponentType::id] = std::make_unique<ComponentSet<ComponentType>>();
		}
	}

	template <typename ComponentType>
	ComponentType* AddComponent()
	{
		if (componentSets.find(ComponentType::id) == componentSets.end())
		{
			return nullptr;
		}

		for (auto& component : static_cast<ComponentSet<ComponentType>*>(componentSets[ComponentType::id].get())->components)
		{
			if (component.IsActive() == false)
			{
				component.SetActive(true);
				return &component;
			}
		}
	}

	template <typename ComponentType>
	ComponentSet<ComponentType>* GetElementSet()
	{
		if (componentSets.find(ComponentType::id) == componentSets.end())
		{
			return nullptr;
		}
		return static_cast<ComponentSet<ComponentType>*>(componentSets[ComponentType::id].get());
	}
};