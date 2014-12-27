#include "SphereCollider.hpp"
#include "Physics.hpp"

SphereCollider::SphereCollider()
{

#ifdef GUINITY_DEBUG
	nCount++;
#endif
}


SphereCollider::~SphereCollider()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "SphereCollider destroyed (" << nCount << " remaining)" << endl;
#endif
}



void SphereCollider::init()
{

	shape = Physics::createSphereCollider(getActor());
}
