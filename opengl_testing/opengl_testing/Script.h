#pragma once

#include "Actor.h"

class Script
#ifdef GUINITY_DEBUG
	:public StaticCounter<Script>
#endif
{
public:
	Script();
	~Script();


	shared_ptr<Actor> getActor();

	void tick(weak_ptr<Actor> a, float deltaSeconds);
	virtual void tick(float deltaSecods) {};


private:
	shared_ptr<Actor> currentActor;

	
};

