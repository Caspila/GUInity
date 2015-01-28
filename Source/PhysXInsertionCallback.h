#pragma once
#include <PxPhysics.h>
#include <PxPhysicsAPI.h>

using namespace physx;

class PhysXInsertionCallback:
	public PxPhysicsInsertionCallback
{
public:
	PhysXInsertionCallback();
	~PhysXInsertionCallback();
};

