#pragma once

//#include "Subject.h"
#include "Enums.hpp"
#include "Module.hpp"

class Component;
class Actor;

class Observer
{
public:
	Observer();
	virtual ~Observer();

	virtual void onNotify(ComponentEventType type, shared_ptr<Component> component, bool isEditor) = 0;
	virtual void onNotify(ActorEventType type, shared_ptr<Actor> actor, bool isEditor) = 0;

};

