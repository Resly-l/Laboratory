#pragma once
#include "crtp.h"

class Entity;

typedef size_t ComponentID;

class ComponentInterface
{
private:
	bool active = false;
	Entity* owner = nullptr;

public:
	virtual ~ComponentInterface() = default;

public:
	bool IsActive() const { return active; }
	void SetActive(bool active) { this->active = active; }

	Entity* GetOwner() const { return owner; }
	void SetOwner(Entity* entity) { owner = entity; }

	virtual void Initialize() {};
};

DECLARE_CRTP(Component, ComponentID)