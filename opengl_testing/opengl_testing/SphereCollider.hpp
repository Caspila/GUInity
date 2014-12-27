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
	virtual~SphereCollider();
	

	//virtual void awake();
	//virtual void tick(float deltaSecods);
	virtual void init();
	//
	//
	//void setTrigger(bool isTrigger);
	//
	//PxShape* shape;
};

