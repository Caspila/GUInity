#pragma once

#include "Collider.hpp"

/** BoxCollider is an AABB collider. Can either be real physics simulated or trigger only. */
class BoxCollider : public Collider
#ifdef GUINITY_DEBUG
	, public StaticCounter<BoxCollider>
#endif
{
private:
	/** The extents of the AABB (half) */
	PxVec3 halfExtent;
public:
	/** Default Constructor */
	BoxCollider();
	/** Deserialization Constructor */
    BoxCollider(PxVec3 halfExtent, PxVec3 center = PxVec3(0,0,0));
	/** Default Destructor*/
	virtual ~BoxCollider();

	/** Init component override. Create a new Box Shape in the PhysX scene. */
	virtual void init();
    
	/** Prototype design pattern*/
	virtual shared_ptr<Component> clone() override;


	/** Serialization region*/
	/** Get a description for the current component*/
	virtual shared_ptr<ComponentDescription> getComponentDescription() ;
	/** Deserialize a component description into this collider */
    virtual void deserialize(shared_ptr<ComponentDescription> desc);
};

