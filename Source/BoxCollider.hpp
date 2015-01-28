#pragma once

#include "Collider.hpp"

class BoxCollider : public Collider
#ifdef GUINITY_DEBUG
	, public StaticCounter<BoxCollider>
#endif
{
public:
	BoxCollider();
    
    BoxCollider(PxVec3 halfExtent, PxVec3 center = PxVec3(0,0,0));
	virtual ~BoxCollider();
    
    PxVec3 halfExtent;
    
	virtual void init();
    
    virtual shared_ptr<ComponentDescription> getComponentDescription() ;
    virtual shared_ptr<Component> clone() { shared_ptr<BoxCollider> compClone = make_shared<BoxCollider>(halfExtent,center);return compClone;};
    
    virtual void deserialize(shared_ptr<ComponentDescription> desc);
};

