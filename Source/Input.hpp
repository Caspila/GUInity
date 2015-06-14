#pragma once

#include "Module.hpp"
#include <vector>
#include <glm/common.hpp>

#include <array>

/** Input class encapsulates the GLFW input functions and allows for more complex input handling (mouse and keyboard for now)
 */
class Input
{
    
private:
    /** Number of mouse buttons */
	const static int nMouseButtons = 8;
    /** Number of keyboard keys */
	const static int nKeys = 300;
    /** Reference to the the GLFWWindow */
	static shared_ptr<GLFWwindow> window;
    
public:
    /** Constructor for a window handle
     @param[in] w GLFWwindow handle
     */
    Input(shared_ptr<GLFWwindow> w);
    /** Default destructor */
    ~Input() { };
    
    /** Keyboard state of all keyboard keys on last frame*/
    static std::array<int, nKeys> oldKeyboardInputState;
    /** Keyboard state of all keyboard keys on current frame*/
    static std::array<int, nKeys> keyboardInputState;
    
    /** Keyboard state of all mouse buttons on last frame*/
    static std::array<int, nMouseButtons> oldMouseInputState;
    /** Keyboard state of all mouse buttons on current frame*/
    static std::array<int, nMouseButtons> mouseInputState;
    
    
    /** Last mouse position x,y on screen */
    static glm::vec2 lastMousePos;
    /** Current mouse position x,y on screen */
    static glm::vec2 mousePos;
    /** Mouse position delta, x,y on screen */
    static glm::vec2 mouseDelta;
    
    
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
    
    /** Updates the state of input. Swaps the old/new and gets the new input state */
    static void updateInputState();
    
    
    /** window Getter
     @return Reference to the GLFWwindow
     */
    static shared_ptr<GLFWwindow> getWindow();
    /** window Setter
     @param window GLFWwindow handle
     */
    static void setWindow(shared_ptr<GLFWwindow> window);
    
    
};
