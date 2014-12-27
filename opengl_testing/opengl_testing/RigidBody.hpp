#pragma once

#include "Module.hpp"
#include "Component.hpp"
#include <PxPhysicsAPI.h>

using namespace physx;

class RigidBody :
	public Component

#ifdef GUINITY_DEBUG
	, public StaticCounter<RigidBody>
#endif
{
public:
	RigidBody();
	virtual ~RigidBody();

	virtual void init() override;
	virtual void tick(float deltaSecods) override;
	virtual void setActive(bool isActive) override;

	PxRigidBody* physxRigidBody;

	void setKinematic(bool isKinematic);

	bool isStatic;

};

