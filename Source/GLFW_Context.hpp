//
//  GLWF_Context.h
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-07-13.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __GUInity_MacOS__GLWF_Context__
#define __GUInity_MacOS__GLWF_Context__

#include <iostream>
#include "GLContext.hpp"
#include "Module.hpp"

class GLFWwindow;

using namespace std;

class GLFW_Context : public GLContext
{
private:
    /** Handle to the window*/
//	shared_ptr<GLFWwindow> window;
    GLFWwindow* window;
public:
    GLFW_Context(GLFWwindow* window);
    GLFW_Context();
    virtual ~GLFW_Context();
    
    virtual void swapBuffers() override;
    virtual int init(int screenWidth, int screenHeight) override;
    virtual void shutdown() override;
    virtual bool shouldClose() override;

};

#endif /* defined(__GUInity_MacOS__GLWF_Context__) */
