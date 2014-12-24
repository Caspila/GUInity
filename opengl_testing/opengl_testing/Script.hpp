#pragma once

#include "Module.hpp"
//#include "Actor.h"

class Actor;

class Script
#ifdef GUINITY_DEBUG
	:public StaticCounter<Script>
#endif
{
public:
	Script();
	~Script();


	shared_ptr<Actor> getActor();

	//void tick(float deltaSeconds);
	//void tick(weak_ptr<Actor> a, float deltaSeconds);
	virtual void tick(float deltaSecods) {};

	void setActor(shared_ptr<Actor> actor);

private:
	shared_ptr<Actor> actor;

	
};

