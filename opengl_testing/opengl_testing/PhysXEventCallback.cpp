#include "PhysXEventCallback.hpp"


PhysXEventCallback::PhysXEventCallback()
{
}


PhysXEventCallback::~PhysXEventCallback()
{
}

void PhysXEventCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{
	cout << "OnContact" << endl;
}
void PhysXEventCallback::onTrigger(PxTriggerPair* pairs, PxU32 count)
{
	cout << "OnTrigger" << endl;
}