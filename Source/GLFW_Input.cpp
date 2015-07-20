//
//  GLFW_Input.cpp
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-07-13.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "GLFW_Input.hpp"



GLFW_Input::GLFW_Input(GLFWwindow* window)
{
    this->window = window;
}



/** Updates the state of input. Swaps the old/new and gets the new input state */
void GLFW_Input::updateInputState()
{
	/** Uses move to prevend copying arrays */
	std::copy(std::begin(keyboardInputState), std::end(keyboardInputState), std::begin(oldKeyboardInputState));
    
	/** Get updated value from GLFW for keyboard state */
	for (int i = 0; i < nKeys; i++)
	{
		keyboardInputState[i] = glfwGetKey(window, i);
	}
    
	/** Uses move to prevend copying arrays */
	std::copy(std::begin(mouseInputState), std::end(mouseInputState), std::begin(oldMouseInputState));
    
	/** Get updated value from GLFW for mouse state */
	for (int i = 0; i < nMouseButtons; i++)
	{
		mouseInputState[i] = glfwGetMouseButton(window, i);
	}
    
	/** Updates mouse position */
	double x, y;
	glfwGetCursorPos(window, &x, &y);
    
	lastMousePos = mousePos;
    
	mousePos.x = x;
	mousePos.y = y;
    
	mouseDelta = mousePos - lastMousePos;
    
}