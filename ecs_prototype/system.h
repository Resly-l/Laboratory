#pragma once
#include "crtp.h"

typedef size_t SystemID;

class SystemInterface
{
private:
	bool active = false;

public:
	virtual ~SystemInterface() = default;

public:
	bool IsActive() const { return active; }
	void SetActive(bool active) { this->active = active; }
	
	virtual void Update() = 0;
};

DECLARE_CRTP(System, SystemID)