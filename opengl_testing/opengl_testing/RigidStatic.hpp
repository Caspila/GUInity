#pragma once
#include "Component.hpp"
#include <PxPhysics.h>
#include "Subject.hpp"
using namespace physx;


class RigidStatic : public Subject<RigidStatic>,
	public Component
{
public:
	RigidStatic();
	~RigidStatic();

	virtual void init() override;
	virtual void tick(float deltaSecods) override;

	PxRigidDynamic* physxRigidStatic;
    
    virtual shared_ptr<ComponentDescription> getComponentDescription();
    virtual shared_ptr<Component> clone() { shared_ptr<RigidStatic> compClone = make_shared<RigidStatic>();return compClone;};
    
    virtual void deserialize(shared_ptr<ComponentDescription> desc);

};

