#pragma once
#include "Component.hpp"
#include <PxPhysics.h>

using namespace physx;

class Collider :
	public Component
{
public:
	Collider();
	virtual ~Collider();

	virtual void awake() {}
	virtual void tick(float deltaSecods) {};
	virtual void init() {};

	//virtual void setActive(bool isActive);
	void setTrigger(bool isTrigger);
	void setQueryOnly(bool queryOnly);

	PxShape* shape;
};

