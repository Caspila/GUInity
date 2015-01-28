#pragma once
#include "Collider.hpp"
#include "Enums.hpp"

class CapsuleCollider :
	public Collider
#ifdef GUINITY_DEBUG
, public StaticCounter<CapsuleCollider>
#endif
{
public:
	CapsuleCollider();
    CapsuleCollider(RotateAxis orientation, float halfHeight, float radius,PxVec3 center);
	~CapsuleCollider();

	virtual void init();

	RotateAxis orientation;
    float halfHeight;
    float radius;

	void setOrientation(RotateAxis orientation);

	void setHeight(float height);

	void setRadius(float radius);

    
    virtual shared_ptr<ComponentDescription> getComponentDescription() ;
    virtual shared_ptr<Component> clone() { shared_ptr<CapsuleCollider> compClone = make_shared<CapsuleCollider>(orientation,halfHeight,radius,center);return compClone;};
    
    virtual void deserialize(shared_ptr<ComponentDescription> desc);
};


