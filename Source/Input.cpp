#include "Input.hpp"
#include "GLFW_Input.hpp"



shared_ptr<InputModule> Input::inputModule;

/** Constructor for a window handle
 @param[in] w GLFWwindow handle
 */
Input::Input(GLFWwindow* window) {
    inputModule = make_shared<GLFW_Input>(window);

};

/** Gets if a key was pressed (press frame only)
 @param[in] keyCode The key
 @return true if key is pressed, false otherwise*/
bool Input::getKeyPressed( int keyCode)
{
    if(inputModule==nullptr)
        return false;
	return inputModule->getKeyPressed(keyCode);
}
/** Returns true if the key was relesed (release frame only)
 @param[in] keyCode The key
 @return true if key was released, false otherwise*/
bool Input::getKeyReleased( int keyCode)
{    if(inputModule==nullptr)
    return false;
    return inputModule->getKeyReleased(keyCode);
}
/** Returns true if the key IS pressed (every frame that the key is pressed)
 @param[in] keyCode The key
 @return true if key is currently being pressed, false otherwise*/
bool Input::getKey( int keyCode)
{    if(inputModule==nullptr)
    return false;
    return inputModule->getKey(keyCode);
}

/** Returns true if the mouse button was pressed (1st frame only)
 @param[in] mouseButtonCode The mouse button
 @return true if mouse button is pressed, false otherwise*/
bool Input::getMouseButtonPressed(int mouseButtonCode)
{    if(inputModule==nullptr)
    return false;
        return inputModule->getMouseButtonPressed(mouseButtonCode);
}
/** Returns true if the mouse button was pressed (release frame only)
 @param[in] mouseButtonCode The mouse button
 @return true if mouse button was released, false otherwise*/
bool Input::getMouseButtonReleased(int mouseButtonCode)
{    if(inputModule==nullptr)
    return false;
    return inputModule->getMouseButtonReleased(mouseButtonCode);
}
/** Returns true if the mouse button IS pressed (every frame that the mouse button is pressed)          @param[in] mouseButtonCode The mouse button
 @return true if mouse button is currently being pressed, false otherwise*/
bool Input::getMouseButton(int mouseButtonCode)
{    if(inputModule==nullptr)
    return false;
    return inputModule->getMouseButton(mouseButtonCode);
}

/** Last mouse position x,y on screen */
glm::vec2 Input::getLastMousePos()
{    if(inputModule==nullptr)
    return glm::vec2(0,0);
    return inputModule->lastMousePos;
}
/** Current mouse position x,y on screen */
glm::vec2 Input::getMousePos()
{if(inputModule==nullptr)
    return glm::vec2(0,0);
    return inputModule->mousePos;
}
/** Mouse position delta, x,y on screen */
glm::vec2 Input::getMouseDelta()
{if(inputModule==nullptr)
    return glm::vec2(0,0);
    return inputModule->mouseDelta;
}

/** Updates the state of input. Swaps the old/new and gets the new input state */
void Input::updateInputState()
{if(inputModule==nullptr)
    return;
    inputModule->updateInputState();
}

