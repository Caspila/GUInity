//
//  InputModule.h
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-07-13.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __GUInity_MacOS__InputModule__
#define __GUInity_MacOS__InputModule__

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

class InputModule
{
protected:
    
    /** Number of mouse buttons */
	const static int nMouseButtons = 8;
    /** Number of keyboard keys */
	const static int nKeys = 300;
    
    /** Keyboard state of all keyboard keys on last frame*/
    std::vector<int> oldKeyboardInputState;
    /** Keyboard state of all keyboard keys on current frame*/
    std::vector<int> keyboardInputState;
    
    /** Keyboard state of all mouse buttons on last frame*/
    std::vector<int> oldMouseInputState;
    /** Keyboard state of all mouse buttons on current frame*/
    std::vector<int> mouseInputState;
    
    

    
public:
    InputModule();
    /** Gets if a key was pressed (press frame only)
     @param[in] keyCode The key
     @return true if key is pressed, false otherwise*/
    bool getKeyPressed( int keyCode);
    /** Returns true if the key was relesed (release frame only)
     @param[in] keyCode The key
     @return true if key was released, false otherwise*/
    bool getKeyReleased(int keyCode);
    /** Returns true if the key IS pressed (every frame that the key is pressed)
     @param[in] keyCode The key
     @return true if key is currently being pressed, false otherwise*/
    bool getKey(int keyCode);
	
    /** Returns true if the mouse button was pressed (1st frame only)
     @param[in] mouseButtonCode The mouse button
     @return true if mouse button is pressed, false otherwise*/
    bool getMouseButtonPressed(int mouseButtonCode);
    /** Returns true if the mouse button was pressed (release frame only)
     @param[in] mouseButtonCode The mouse button
     @return true if mouse button was released, false otherwise*/
    bool getMouseButtonReleased(int mouseButtonCode);
    /** Returns true if the mouse button IS pressed (every frame that the mouse button is pressed)
     @param[in] mouseButtonCode The mouse button
     @return true if mouse button is currently being pressed, false otherwise*/
    bool getMouseButton(int mouseButtonCode);
    
    /** Last mouse position x,y on screen */
    glm::vec2 getLastMousePos();
    /** Current mouse position x,y on screen */
    glm::vec2 getMousePos();
    /** Mouse position delta, x,y on screen */
    glm::vec2 getMouseDelta();
    
    /** Last mouse position x,y on screen */
    glm::vec2 lastMousePos;
    /** Current mouse position x,y on screen */
    glm::vec2 mousePos;
    /** Mouse position delta, x,y on screen */
    glm::vec2 mouseDelta;

    /** Updates the state of input. Swaps the old/new and gets the new input state */
    virtual void updateInputState() = 0;
    
};

#endif /* defined(__GUInity_MacOS__InputModule__) */
