#pragma once
#include "Collider.hpp"

class MeshCollider : public Collider
#ifdef GUINITY_DEBUG
	, public StaticCounter<MeshCollider>
#endif
{
public:
	MeshCollider();
	virtual ~MeshCollider();

	virtual void init();
    virtual void tick(float deltaSeconds) override;
    
};

