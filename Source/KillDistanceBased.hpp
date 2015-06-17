//
//  KillDistanceBased.h
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-06-17.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __GUInity_MacOS__KillDistanceBased__
#define __GUInity_MacOS__KillDistanceBased__

#include <iostream>

#include "Module.hpp"
#include "ScriptComponent.hpp"
#include "Input.hpp"
#include "Transform.hpp"


class Material;
class Mesh;


class KillDistanceBased : public ScriptComponent
{
public:
    float distanceToKill = 15;
    
    weak_ptr<Actor> playerRef;
    
    virtual void awake() override;
    virtual void tick(float deltaSeconds) override;
    
    float checkInterval = 0.5f;
    float elapsedTime = 0.0f;
    
    void checkDeath();
    
    virtual shared_ptr<Component> clone() override;
};
#endif /* defined(__GUInity_MacOS__KillDistanceBased__) */
