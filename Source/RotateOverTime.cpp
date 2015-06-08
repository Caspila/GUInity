//
//  RotateOverTime.cpp
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-20.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "ScriptComponent.hpp"
#include "RotateOverTime.hpp"
#include "Actor.hpp"
#include "Transform.hpp"

void RotateOverTime::tick(float deltaSeconds)
{
    std:: cout << "Rotating" << endl;
    getActor()->transform->rotation =  glm::angleAxis(deltaSeconds, glm::vec3(1, 0, 0))* getActor()->transform->rotation;
}