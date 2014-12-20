#pragma once
#include "Module.h"
#include <PxPhysics.h>

using namespace physx;

class PhysicsMaterial
{
public:
	PhysicsMaterial(float friction, float dynamicFriction, float restitution, shared_ptr<PxMaterial> material);
	~PhysicsMaterial();

	float friction, dynamicFriction, restitution;

	shared_ptr<PxMaterial> material;
};

