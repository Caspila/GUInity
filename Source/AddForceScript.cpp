//
//  AddForceScript.cpp
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-21.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "Input.hpp"
#include "AddForceScript.hpp"
#include "Actor.hpp"
#include "RigidBody.hpp"


void AddForceScript::tick(float deltaSeconds)
{
   shared_ptr<RigidBody> rigidBody = getActor()->GetComponent<RigidBody>();

    if(Input::getKeyPressed(GLFW_KEY_0))

        rigidBody->addForce(glm::vec3(0,0,100));
}