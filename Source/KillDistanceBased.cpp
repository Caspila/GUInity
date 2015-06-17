//
//  KillDistanceBased.cpp
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-06-17.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "KillDistanceBased.hpp"
#include "Actor.hpp"
#include "World.hpp"
#include "Factory.hpp"
#include "Game.hpp"


void KillDistanceBased::awake()
{
    playerRef = Game::world->findActor("SpaceShip");
}
void KillDistanceBased::tick(float deltaSeconds)
{
    elapsedTime += deltaSeconds;
    if(elapsedTime > checkInterval)
    {
        checkDeath();
        elapsedTime = 0.0f;
    }
    

    
}

void KillDistanceBased::checkDeath()
{
    if(playerRef.lock())
    {
        float distance = glm::distance(glm::vec3(),getActor()->transform->getWorldPosition());
        
        if(distance >= distanceToKill)
        {
            Factory::DestroyActor(getActor());
        }
    }
}

shared_ptr<Component> KillDistanceBased::clone()
{
    shared_ptr<KillDistanceBased> cloned = make_shared<KillDistanceBased>();
    
    return cloned;
}