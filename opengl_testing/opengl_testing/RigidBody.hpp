#pragma once

#include "Module.hpp"
#include "Component.hpp"
#include <PxPhysicsAPI.h>
#include "Subject.hpp"

using namespace physx;

class RigidBody : public Subject<RigidBody>,
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
    
    // Every RigidBody will have a D6 joint to allow for locking degrees of freedom
//    PxD6Joint* d6Joint;
    
	void setKinematic(bool isKinematic);

    bool getKinematic();
    
    bool lockMoveX,lockMoveY,lockMoveZ;
    bool lockRotateX,lockRotateY,lockRotateZ;
    
    void setMoveEnabled(TransformAxis axis, bool enabled);
    void setRotateEnabled(TransformAxis axis, bool enabled);
    
    void updateTransform(const PxTransform& transform);
    
    virtual shared_ptr<ComponentDescription> getComponentDescription();
    virtual shared_ptr<Component> clone() { shared_ptr<RigidBody> compClone = make_shared<RigidBody>();return compClone;};
    
    virtual void deserialize(shared_ptr<ComponentDescription> desc);
    
    void addForce(glm::vec3 axis);


    
};

