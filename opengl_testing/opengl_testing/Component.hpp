#pragma once

#include "Module.hpp"

class Actor;

class Component
//#ifdef GUINITY_DEBUG
//	:public StaticCounter<Component>
//#endif
{
public:
	Component();
	virtual ~Component();

	virtual void setActive(bool isActive) {};

	virtual void awake() {};
	virtual void tick(float deltaSecods) {};
	virtual void init() {};

	weak_ptr<Actor> actor;

	shared_ptr<Actor> getActor();
	void setActor(weak_ptr<Actor> actor);

#ifdef GUINITY_DEBUG
	static int count;
#endif
};

