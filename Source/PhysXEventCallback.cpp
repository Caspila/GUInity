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
    if( pairHeader.flags & (PxContactPairHeaderFlag::eDELETED_ACTOR_0 | PxContactPairHeaderFlag::eDELETED_ACTOR_1) )
        return;
    
	PxActor* ac1 = pairHeader.actors[0];
	PxActor* ac2 = pairHeader.actors[1];

	shared_ptr<Actor> actor1 = (static_cast<Actor*>(ac1->userData))->shared_from_this();
	shared_ptr<Actor> actor2 = (static_cast<Actor*>(ac2->userData))->shared_from_this();;

	actor1->triggerPhysxCollision(actor2);
	actor2->triggerPhysxCollision(actor1);

	
	for (int i = 0; i < nbPairs; i++)
	{
		PxContactPair pair =  pairs[i];
	}
}
void PhysXEventCallback::onTrigger(PxTriggerPair* pairs, PxU32 nbPairs)
{

	for (int i = 0; i < nbPairs; i++)
	{
        // Check if shapes were deleted
        if( pairs[i].flags & (PxTriggerPairFlag::eDELETED_SHAPE_TRIGGER | PxTriggerPairFlag::eDELETED_SHAPE_OTHER) )
        {
            continue;
        }
        
		PxTriggerPair pair = pairs[i];

		PxActor* ac1 = pair.triggerActor;
		PxActor* ac2 = pair.otherActor;

        shared_ptr<Actor> actor1 = (static_cast<Actor*>(ac1->userData))->shared_from_this();
        shared_ptr<Actor> actor2 = (static_cast<Actor*>(ac2->userData))->shared_from_this();;

        actor1->triggerPhysxTrigger(actor2);
        actor2->triggerPhysxTrigger(actor1);

	}
}