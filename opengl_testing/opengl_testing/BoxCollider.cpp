#include "BoxCollider.hpp"
#include "Physics.hpp"


using namespace physx;

BoxCollider::BoxCollider()
{

#ifdef GUINITY_DEBUG
	nCount++;
#endif
}


BoxCollider::~BoxCollider()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "BoxCollider destroyed (" << nCount << " remaining)" << endl;
#endif
}

void BoxCollider::init()
{

	shape = Physics::createBoxCollider(getActor());
}

