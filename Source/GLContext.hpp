//
//  GLContext.h
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-07-13.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __GUInity_MacOS__GLContext__
#define __GUInity_MacOS__GLContext__

#include <iostream>


class GLContext
{
public:
    virtual int init(int screenWidth, int screenHeight) = 0;
    virtual void shutdown() = 0;
    virtual void swapBuffers() = 0;
    virtual bool shouldClose() = 0;

    
};


#endif /* defined(__GUInity_MacOS__GLContext__) */
