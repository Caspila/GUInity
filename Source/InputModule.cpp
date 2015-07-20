//
//  InputModule.cpp
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-07-13.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include <stdio.h>
#include "InputModule.hpp"

InputModule::InputModule()
{
    oldKeyboardInputState.resize(nKeys);
        keyboardInputState.resize(nKeys);

    oldMouseInputState.resize(nMouseButtons);
    mouseInputState.resize(nMouseButtons);
    
}

/** Gets if a key was pressed (press frame only)
 @param[in] keyCode The key
 @return true if key is pressed, false otherwise*/
bool InputModule::getKeyPressed( int keyCode)
{
	return !oldKeyboardInputState[keyCode] && keyboardInputState[keyCode];
}
/** Returns true if the key was relesed (release frame only)
 @param[in] keyCode The key
 @return true if key was released, false otherwise*/
bool InputModule::getKeyReleased( int keyCode)
{
	return oldKeyboardInputState[keyCode] && !keyboardInputState[keyCode];
}
/** Returns true if the key IS pressed (every frame that the key is pressed)
 @param[in] keyCode The key
 @return true if key is currently being pressed, false otherwise*/
bool InputModule::getKey( int keyCode)
{
	return keyboardInputState[keyCode];
}

/** Returns true if the mouse button was pressed (1st frame only)
 @param[in] mouseButtonCode The mouse button
 @return true if mouse button is pressed, false otherwise*/
bool InputModule::getMouseButtonPressed(int mouseButtonCode)
{
	return !oldMouseInputState[mouseButtonCode] && mouseInputState[mouseButtonCode];
}
/** Returns true if the mouse button was pressed (release frame only)
 @param[in] mouseButtonCode The mouse button
 @return true if mouse button was released, false otherwise*/
bool InputModule::getMouseButtonReleased(int mouseButtonCode)
{
	return oldMouseInputState[mouseButtonCode] && !mouseInputState[mouseButtonCode];
}
/** Returns true if the mouse button IS pressed (every frame that the mouse button is pressed)          @param[in] mouseButtonCode The mouse button
 @return true if mouse button is currently being pressed, false otherwise*/
bool InputModule::getMouseButton(int mouseButtonCode)
{
	return mouseInputState[mouseButtonCode];
}
/** Last mouse position x,y on screen */
glm::vec2 InputModule::getLastMousePos()
{
    return lastMousePos;
}
/** Current mouse position x,y on screen */
glm::vec2 InputModule::getMousePos()
{
       return mousePos;
}
/** Mouse position delta, x,y on screen */
glm::vec2 InputModule::getMouseDelta()
{
        return mouseDelta;
}