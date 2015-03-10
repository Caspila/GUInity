#pragma once

#include "Collider.hpp"

class SphereCollider :

	public Collider
#ifdef GUINITY_DEBUG
	, public StaticCounter<SphereCollider>
#endif
{
private:
	/** The radius of the Sphere */
	float radius;

public:
	/** Default Constructor*/
	SphereCollider();
	/** Deserialization Constructor*/
    SphereCollider(float radius, PxVec3 center);
	/** Default Destructor*/
	virtual ~SphereCollider();
	
	/** radius Getter*/
	float getRadius();
	/** radius Setter*/
	void setRadius(float newRadius);

	/** Init component override. Create a new Sphere Shape in the PhysX scene. */
	virtual void init();
	
	/** Prototype design pattern*/
	virtual shared_ptr<Component> clone() { shared_ptr<SphereCollider> compClone = make_shared<SphereCollider>(radius,center); return compClone; };

	/** Serialization region*/
	/** Get a description for the current component*/
	virtual shared_ptr<ComponentDescription> getComponentDescription();
	/** Deserialize a component description into this collider */
	virtual void deserialize(shared_ptr<ComponentDescription> desc);
};

