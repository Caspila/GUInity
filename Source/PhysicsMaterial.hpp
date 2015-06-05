#pragma once
#include "Module.hpp"
#include "Asset.hpp"
#include <PxPhysics.h>

using namespace physx;

class PhysicsMaterial : public Asset
#ifdef GUINITY_DEBUG
	, public StaticCounter<PhysicsMaterial>
#endif
{
private:
	//PxMaterial*  material;
	PxMaterial*  material;

public:
	//PhysicsMaterial(float friction, float dynamicFriction, float restitution, shared_ptr<PxMaterial> material);
	PhysicsMaterial(float friction, float dynamicFriction, float restitution);
	virtual ~PhysicsMaterial();

	float friction, dynamicFriction, restitution;
    
	PxMaterial*   getMaterial();

};

