//
//  GLWF_Context.cpp
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-07-13.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "GLFW_Context.hpp"
#include "Module.hpp"
#include <glfw/glfw3.h>

GLFW_Context::GLFW_Context()
{
    window = nullptr;
}

GLFW_Context::GLFW_Context(GLFWwindow* window)
{
//    this->window.reset(window);
    this->window = window;
}

GLFW_Context::~GLFW_Context()
{
    window = nullptr;
}


int GLFW_Context::init(int screenWidth, int screenHeight)
{
    if(window==nullptr)
    {
    if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    window =glfwCreateWindow(screenWidth, screenHeight, "Hello Triangle", NULL, NULL);
//	window.reset(glfwCreateWindow(screenWidth, screenHeight, "Hello Triangle", NULL, NULL), glfwDestroyWindow);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
//	glfwMakeContextCurrent(window.get());
             	glfwMakeContextCurrent(window);
    
    }
    return 0;
}

void GLFW_Context::swapBuffers()
{
    glfwPollEvents();
    // put the stuff we've been drawing onto the display
//    glfwSwapBuffers(window.get());
     glfwSwapBuffers(window);
}

void GLFW_Context::shutdown()
{
    glfwDestroyWindow(window);
//        glfwDestroyWindow(window.get());
    glfwTerminate();
}

bool GLFW_Context::shouldClose()
{
//    return glfwWindowShouldClose(window.get());
        return glfwWindowShouldClose(window);
}