#include "Input.hpp"

shared_ptr<GLFWwindow> Input::window;

/** Keyboard state of all keyboard keys on last frame*/
std::array<int, Input::nKeys> Input::oldKeyboardInputState = { 0 };
/** Keyboard state of all keyboard keys on current frame*/
std::array<int, Input::nKeys> Input::keyboardInputState = { 0 };

/** Keyboard state of all mouse buttons on last frame*/
std::array<int, Input::nMouseButtons > Input::oldMouseInputState = { 0 };
/** Keyboard state of all mouse buttons on current frame*/
std::array<int, Input::nMouseButtons> Input::mouseInputState = { 0 };

/** Last mouse position x,y on screen */
glm::vec2 Input::lastMousePos;
/** Current mouse position x,y on screen */
glm::vec2 Input::mousePos;
/** Mouse position delta, x,y on screen */
glm::vec2 Input::mouseDelta;

/** Constructor for a window handle */
Input::Input(shared_ptr<GLFWwindow> w) {
	window = w;
};

/** Returns true if the key was pressed (1st frame only) */
bool Input::getKeyPressed( int keyCode)
{
	return !oldKeyboardInputState[keyCode] && keyboardInputState[keyCode];
}
/** Returns true if the key was pressed (release frame only) */
bool Input::getKeyReleased( int keyCode)
{
	return oldKeyboardInputState[keyCode] && !keyboardInputState[keyCode];
}
/** Returns true if the key IS pressed (every frame that the key is pressed) */
bool Input::getKey( int keyCode)
{
	return keyboardInputState[keyCode];
}

/** Returns true if the mouse button was pressed (1st frame only) */
bool Input::getMouseButtonPressed(int keyCode)
{
	return !oldMouseInputState[keyCode] && mouseInputState[keyCode];
}
/** Returns true if the mouse button was pressed (release frame only) */
bool Input::getMouseButtonReleased(int keyCode)
{
	return oldMouseInputState[keyCode] && !mouseInputState[keyCode];
}
/** Returns true if the mouse button IS pressed (every frame that the mouse button is pressed) */
bool Input::getMouseButton(int keyCode)
{
	return mouseInputState[keyCode];
}

/** Updates the state of input. Swaps the old/new and gets the new input state */
void Input::updateInputState()
{
	/** Uses move to prevend copying arrays */
	std::copy(std::begin(keyboardInputState), std::end(keyboardInputState), std::begin(oldKeyboardInputState));

	/** Get updated value from GLFW for keyboard state */
	for (int i = 0; i < nKeys; i++)
	{
		keyboardInputState[i] = glfwGetKey(window.get(), i);
	}

	/** Uses move to prevend copying arrays */
	std::copy(std::begin(mouseInputState), std::end(mouseInputState), std::begin(oldMouseInputState));

	/** Get updated value from GLFW for mouse state */
	for (int i = 0; i < nMouseButtons; i++)
	{
		mouseInputState[i] = glfwGetMouseButton(window.get(), i);
	}

	/** Updates mouse position */
	double x, y;
	glfwGetCursorPos(window.get(), &x, &y);

	lastMousePos = mousePos;

	mousePos.x = x;
	mousePos.y = y;

	mouseDelta = mousePos - lastMousePos;

}