#include "PhysXEventCallback.hpp"
#include "Actor.hpp"


PhysXEventCallback::PhysXEventCallback()
{
}


PhysXEventCallback::~PhysXEventCallback()
{
}

void PhysXEventCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{
	cout << "OnContact" << endl;

	PxActor* ac1 = pairHeader.actors[0];
	PxActor* ac2 = pairHeader.actors[1];

	Actor* actor1 = static_cast<Actor*>(ac1->userData);
	Actor* actor2 = static_cast<Actor*>(ac2->userData);

	actor1->triggerPhysxCollision(actor2);
	actor2->triggerPhysxCollision(actor1);

	
	for (int i = 0; i < nbPairs; i++)
	{
		PxContactPair pair =  pairs[i];
	}
}
void PhysXEventCallback::onTrigger(PxTriggerPair* pairs, PxU32 nbPairs)
{
	cout << "OnTrigger" << endl;

	for (int i = 0; i < nbPairs; i++)
	{
		PxTriggerPair pair = pairs[i];

		PxActor* ac1 = pair.triggerActor;// .shapes[0];
		PxActor* ac2 = pair.otherActor;

		Actor* actor1 = static_cast<Actor*>(ac1->userData);
		Actor* actor2 = static_cast<Actor*>(ac2->userData);

		actor1->triggerPhysxTrigger(actor2);
		actor2->triggerPhysxTrigger(actor1);
	}
}