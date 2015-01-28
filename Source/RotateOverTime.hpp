//
//  RotateOverTime.h
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-20.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __opengl_testing_mag__RotateOverTime__
#define __opengl_testing_mag__RotateOverTime__

#include <iostream>



class RotateOverTime : public ScriptComponent
{
public:
    void tick(float deltaSeconds) override;
};

#endif /* defined(__opengl_testing_mag__RotateOverTime__) */
