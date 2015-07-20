#pragma once

#include "Module.hpp"
#include <vector>
#include <glm/common.hpp>
#include <GLFW/glfw3.h>

#include <array>
#include "InputModule.hpp"

/** Input class encapsulates the GLFW input functions and allows for more complex input handling (mouse and keyboard for now)
 */
class Input
{
    
private:

    static shared_ptr<InputModule> inputModule;
    
public:
    /** Constructor for a window handle
     @param[in] w GLFWwindow handle
     */
    Input(GLFWwindow* window);
    /** Default Constructor */
    Input() {};
    /** Default destructor */
    ~Input() { };

    /** Gets if a key was pressed (press frame only)
     @param[in] keyCode The key
     @return true if key is pressed, false otherwise*/
    static bool getKeyPressed( int keyCode);
    /** Returns true if the key was relesed (release frame only)
     @param[in] keyCode The key
     @return true if key was released, false otherwise*/
    static bool getKeyReleased(int keyCode);
    /** Returns true if the key IS pressed (every frame that the key is pressed)
     @param[in] keyCode The key
     @return true if key is currently being pressed, false otherwise*/
    static bool getKey(int keyCode);
	
    /** Returns true if the mouse button was pressed (1st frame only)
     @param[in] mouseButtonCode The mouse button
     @return true if mouse button is pressed, false otherwise*/
    static bool getMouseButtonPressed(int mouseButtonCode);
    /** Returns true if the mouse button was pressed (release frame only)
     @param[in] mouseButtonCode The mouse button
     @return true if mouse button was released, false otherwise*/
    static bool getMouseButtonReleased(int mouseButtonCode);
    /** Returns true if the mouse button IS pressed (every frame that the mouse button is pressed)         
     @param[in] mouseButtonCode The mouse button
     @return true if mouse button is currently being pressed, false otherwise*/
    static bool getMouseButton(int mouseButtonCode);
    
    /** Last mouse position x,y on screen */
    static glm::vec2 getLastMousePos();
    /** Current mouse position x,y on screen */
    static glm::vec2 getMousePos();
    /** Mouse position delta, x,y on screen */
    static glm::vec2 getMouseDelta();
    
    /** Updates the state of input. Swaps the old/new and gets the new input state */
    static void updateInputState();
    

    
    
};
