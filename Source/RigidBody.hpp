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
private:

	PxRigidBody* physxRigidBody;

public:
	RigidBody();
	virtual ~RigidBody();

	virtual void init() override;
    virtual void destroy() override;
	virtual void tick(float deltaSecods) override;
	virtual void setActive(bool isActive) override;

    
    // Every RigidBody will have a D6 joint to allow for locking degrees of freedom
//    PxD6Joint* d6Joint;
    
	PxRigidBody* getRigidbody();
	
	void setKinematic(bool isKinematic);

    bool getKinematic();
    
    bool lockMoveX,lockMoveY,lockMoveZ;
    bool lockRotateX,lockRotateY,lockRotateZ;
    bool isKinematic;
    bool gravityEnabled;
    
    void setMoveEnabled(TransformAxis axis, bool enabled);
    void setRotateEnabled(TransformAxis axis, bool enabled);
    
    void updateTransform(const PxTransform& transform);
    
    virtual shared_ptr<ComponentDescription> getComponentDescription();
    virtual shared_ptr<Component> clone() override;
    
    virtual void deserialize(shared_ptr<ComponentDescription> desc);
    
    void addForce(glm::vec3 axis);

	void setGravity(bool enabled);
	bool getGravity();
    
};

