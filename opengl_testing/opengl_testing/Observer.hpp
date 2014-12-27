#pragma once

//#include "Subject.h"
#include "Enums.hpp"
#include "Module.hpp"

class Component;

class Observer
{
public:
	Observer();
	virtual ~Observer();

	virtual void onNotify(EventType type, shared_ptr<Component> component) = 0;

};

