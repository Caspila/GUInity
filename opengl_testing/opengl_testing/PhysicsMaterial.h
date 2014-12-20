#pragma once
#include "Module.h"
#include <PxPhysics.h>

using namespace physx;

class PhysicsMaterial
#ifdef GUINITY_DEBUG
	:public StaticCounter<PhysicsMaterial>
#endif
{
public:
	PhysicsMaterial(float friction, float dynamicFriction, float restitution, shared_ptr<PxMaterial> material);
	~PhysicsMaterial();

	float friction, dynamicFriction, restitution;

	shared_ptr<PxMaterial> material;

};

