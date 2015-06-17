//
//  KillOnCollision.cpp
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-06-15.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "KillOnCollision.hpp"
#include "Actor.hpp"
#include "Factory.hpp"
#include "Collider.hpp"
#include "Math.hpp"
#include "PointsTracker.hpp"

void KillOnCollision::awake()
{
    colliderName = "Missile";
}


void KillOnCollision::onTrigger(shared_ptr<Actor> actor)
{
    if (actor->name.compare(colliderName) == 0)
    {
        cout << "Collided" << endl;
        //        Factory::DestroyActor(actor->shared_from_this());
        
        
        
        shared_ptr<Actor> myActor = getActor();
        if(myActor)
        {
            glm::vec3 currentScale = myActor->transform->getScale();
            
            PointsTracker::changeScore(10);
            
            if(currentScale.x > 0.2f)
            {
                
                currentScale = currentScale * 0.5f;
                
                float forceScale = 50;
                
                
                shared_ptr<Actor> newAsteroid1 = myActor->clone();
                newAsteroid1->transform->setScale(currentScale);
                newAsteroid1->GetComponent<RigidBody>()->addForce(randUnitVectorXY() * forceScale);
                newAsteroid1->GetComponent<RigidBody>()->addTorque(randUnitVectorXY() * forceScale);
                newAsteroid1->GetComponent<Collider>()->recalculateBounds();
                
                newAsteroid1->name = "Asteroid";
                
                shared_ptr<Actor> newAsteroid2 = myActor->clone();
                newAsteroid2->transform->setScale(currentScale);
                newAsteroid2->GetComponent<RigidBody>()->addForce(randUnitVectorXY() * forceScale);
                newAsteroid2->GetComponent<RigidBody>()->addTorque(randUnitVectorXY() * forceScale);
                newAsteroid2->GetComponent<Collider>()->recalculateBounds();
                
                newAsteroid2->name = "Asteroid";
            }
        }
        
        Factory::DestroyActor(myActor->shared_from_this());
        Factory::DestroyActor(actor->shared_from_this());
    }
    
    
}

shared_ptr<Component> KillOnCollision::clone()
{
    shared_ptr<KillOnCollision> cloned = make_shared<KillOnCollision>();
    cloned->colliderName = colliderName;
    
    return cloned;
}