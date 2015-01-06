#pragma once
#include "Component.hpp"
#include <PxPhysics.h>

#include "MeshFilter.hpp"

using namespace physx;

class Collider :
	public Component
{
public:
	Collider();
	virtual ~Collider();

	virtual void awake() {}
	virtual void tick(float deltaSecods) {};
	virtual void init() {};

	//virtual void setActive(bool isActive);
	void setTrigger(bool isTrigger);
	void setQueryOnly(bool queryOnly);

    
    virtual shared_ptr<ComponentDescription> getComponentDescription() {return make_shared<ColliderDescription>();};
    virtual shared_ptr<Component> clone() { shared_ptr<Collider> compClone = make_shared<Collider>();return compClone;};
    
    virtual void deserialize(shared_ptr<ComponentDescription> desc) {};

    PxVec3 center;
	PxShape* shape;
    bool initWithData;
};

