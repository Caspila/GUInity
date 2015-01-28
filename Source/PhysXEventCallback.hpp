#pragma once

#include "Module.hpp"
#include <PxPhysicsAPI.h>
#include <PxPhysics.h>

using namespace physx;

class PhysXEventCallback : public PxSimulationEventCallback
{
public:
	PhysXEventCallback();
	~PhysXEventCallback();


	virtual void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) override {};
	virtual void onWake(PxActor** actors, PxU32 count) override {};
	virtual void onSleep(PxActor** actors, PxU32 count) override {};

	virtual void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs) override;
	virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) override;
};

