#pragma once

#include "Collider.hpp"

class SphereCollider :

	public Collider
#ifdef GUINITY_DEBUG
	, public StaticCounter<SphereCollider>
#endif
{
public:
	SphereCollider();
    SphereCollider(float radius, PxVec3 center);
	virtual~SphereCollider();
	
    float radius;

	virtual void init();
	
    virtual shared_ptr<ComponentDescription> getComponentDescription() ;
    virtual shared_ptr<Component> clone() { shared_ptr<SphereCollider> compClone = make_shared<SphereCollider>(radius,center);return compClone;};
    
    virtual void deserialize(shared_ptr<ComponentDescription> desc);
};

