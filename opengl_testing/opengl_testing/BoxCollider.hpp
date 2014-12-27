#pragma once

#include "Collider.hpp"

class BoxCollider : public Collider
#ifdef GUINITY_DEBUG
	, public StaticCounter<BoxCollider>
#endif
{
public:
	BoxCollider();
	virtual ~BoxCollider();


	//virtual void awake();
	//virtual void tick(float deltaSecods);
	virtual void init();

	//void setTrigger(bool isTrigger);
	//
	//PxShape* shape;
};

