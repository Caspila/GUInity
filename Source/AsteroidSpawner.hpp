//
//  AsteroidSpawner.h
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-06-16.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __GUInity_MacOS__AsteroidSpawner__
#define __GUInity_MacOS__AsteroidSpawner__

#include <iostream>

#include "Module.hpp"
#include "ScriptComponent.hpp"
#include "Input.hpp"
#include "Transform.hpp"

class AsteroidSpawner : public ScriptComponent
{
public:
    
    void awake() override;
    void tick(float deltaSeconds) override;
    void         spawnAsteroid();
    void         createAsteroidPrefab();
    
    float elapsedTime;
    float waitTime;
    float minWaitTime;
    float maxWaitTime;
    
    float spawnRadius = 10;
    
    shared_ptr<Actor> asteroidPrefab;
};

#endif /* defined(__GUInity_MacOS__AsteroidSpawner__) */
