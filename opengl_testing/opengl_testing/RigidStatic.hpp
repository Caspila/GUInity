#pragma once
#include "Component.hpp"
#include <PxPhysics.h>

using namespace physx;


class RigidStatic :
	public Component
{
public:
	RigidStatic();
	~RigidStatic();

	virtual void init() override;
	virtual void tick(float deltaSecods) override;

	PxRigidDynamic* physxRigidStatic;

};

