//
//  GLFW_Input.h
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-07-13.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __GUInity_MacOS__GLFW_Input__
#define __GUInity_MacOS__GLFW_Input__

#include <iostream>
#include "Input.hpp"

class GLFW_Input : public InputModule
{
public:
    GLFW_Input(GLFWwindow* window);
    /** Reference to the the GLFWWindow */
	GLFWwindow* window;
    
    /** window Getter
     @return Reference to the GLFWwindow
     */
    GLFWwindow* getWindow();
    /** window Setter
     @param window GLFWwindow handle
     */
    void setWindow(GLFWwindow* window);
    
    /** Updates the state of input. Swaps the old/new and gets the new input state */
    virtual void updateInputState() override;
};

#endif /* defined(__GUInity_MacOS__GLFW_Input__) */
