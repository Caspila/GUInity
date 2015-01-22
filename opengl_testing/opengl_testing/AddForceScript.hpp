//
//  AddForceScript.h
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-21.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __opengl_testing_mag__AddForceScript__
#define __opengl_testing_mag__AddForceScript__

#include <iostream>
#include "ScriptComponent.hpp"

class AddForceScript : public ScriptComponent
{
public:
    void tick(float deltaSeconds) override;
};
#endif /* defined(__opengl_testing_mag__AddForceScript__) */
