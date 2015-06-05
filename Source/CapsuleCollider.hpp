#pragma once
#include "Collider.hpp"
#include "Enums.hpp"

class CapsuleCollider :
	public Collider
#ifdef GUINITY_DEBUG
, public StaticCounter<CapsuleCollider>
#endif
{
private:
	/** The orientation of the Capsule (X,Y,Z) */
	RotateAxis orientation;
	/** The height of the Capsule (half) */
	float halfHeight;
	/** The radius of the Capsule */
	float radius;
public:
	/** Default Constructor*/
	CapsuleCollider();
	/** Deserialization Constructor*/
    CapsuleCollider(RotateAxis orientation, float halfHeight, float radius,PxVec3 center);
	/** Default Destructor*/
	~CapsuleCollider();

	/** orientation Setter*/
	void setOrientation(RotateAxis orientation);
	/** orientation Getter*/
	RotateAxis getOrientation();

	/** height Setter*/
	void setHeight(float height);
	/** height Getter*/
	float getHeight();

	/** radius Setter*/
	void setRadius(float radius);
	/** radius Getter*/
	float getRadius();

	/** Init component override. Create a new Capsule Shape in the PhysX scene. */
	virtual void init();

	
	/** Prototype design pattern*/
	virtual shared_ptr<Component> clone() override;

	/** Serialization region*/
	/** Get a description for the current component*/
    virtual shared_ptr<ComponentDescription> getComponentDescription() ;
	/** Deserialize a component description into this collider */
    virtual void deserialize(shared_ptr<ComponentDescription> desc);

};


