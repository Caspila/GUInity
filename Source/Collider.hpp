#pragma once
#include "Component.hpp"
#include <PxPhysics.h>

#include "MeshFilter.hpp"

using namespace physx;

/** Collider is a component that adds physics and trigger collision behaviour to an actor.
	Collider is meant to be a parent class for all the Collider types (Sphere, Box, Capsule and Mesh) */
class Collider :
	public Component
{
protected:
	/** The center of the collider */
	PxVec3 center;
	/** The PhysX Shape of the collider */
	PxShape* shape;
	/** Used when been deserialized */
	bool initWithData;

public:
	/** Default Constructor */
	Collider() {};
	/** Default Destructor. Virtual because it's parent class */
	virtual ~Collider() {};

	/** Component Awake override */
	virtual void awake() override{}
	/** Component Init override */
	virtual void init() override{};
	/** Component setActive override */
    virtual void setActive(bool isActive) override;

	/** Is this collider a trigger or should it simulate real world physics? */
	void setTrigger(bool isTrigger);
	/** isTrigger getter*/
	bool getIsTrigger();
	/** Is this collider used for queries only? */
	void setQueryOnly(bool queryOnly);
	/** queryOnly getter*/
	bool getQueryOnly();

	/** Prototype design pattern*/
	virtual shared_ptr<Component> clone() { shared_ptr<Collider> compClone = make_shared<Collider>(); return compClone; };

	/** Serialization region*/
	/** Get a description for the current component*/
    virtual shared_ptr<ComponentDescription> getComponentDescription() {return make_shared<ColliderDescription>();};
	/** Deserialize a component description into this collider */
    virtual void deserialize(shared_ptr<ComponentDescription> desc) {};

    
};

