#pragma once

#include "Actor.h"

class Script
{
public:
	Script();
	~Script();


	shared_ptr<Actor> getActor();

	void tick(shared_ptr<Actor> a, float deltaSeconds);
	virtual void tick(float deltaSecods) {};


private:
	shared_ptr<Actor> currentActor;

	
};

