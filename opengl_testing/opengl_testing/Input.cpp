#include "Input.h"

//void Input::setWindow(shared_ptr<GLFWwindow> window)
//{
//	this->window = window;
//}

//bool Input::getKeyPressed(GLFWwindow* window, int keyCode)
//{
//	bool previous = inputState[keyCode];
//
//	inputState[keyCode] = glfwGetKey(window, keyCode);
//
//	int result = glfwGetKey(window, keyCode);
//
//	return !previous && inputState[keyCode];
//
//}
//bool Input::getKeyReleased(GLFWwindow* window, int keyCode)
//{
//	bool previous = inputState[keyCode];
//
//	inputState[keyCode] = glfwGetKey(window, keyCode);
//
//	int result = glfwGetKey(window, keyCode);
//
//	return previous && !inputState[keyCode];
//}
//bool Input::getKey(GLFWwindow* window, int keyCode)
//{
//	inputState[keyCode] = glfwGetKey(window, keyCode);
//
//	return inputState[keyCode];
//}
//
//bool Input::getKeyPressed(GLFWwindow* window, int keyCode)
//{
//	return !oldInputState[keyCode] && inputState[keyCode];
//}
//bool Input::getKeyReleased(GLFWwindow* window, int keyCode)
//{
//	return oldInputState[keyCode] && !inputState[keyCode];
//}
//bool Input::getKey(GLFWwindow* window, int keyCode)
//{
//	return inputState[keyCode];
//}
//
//void Input::updateKeyboardState(GLFWwindow* window)
//{
//	std::copy(std::begin(inputState), std::end(inputState), std::begin(oldInputState));
//
//	for (int i = 0; i < nKeys; i++)
//	{
//		inputState[i] = glfwGetKey(window, i);
//	}
//
//}


std::vector<int> Input::oldKeyboardInputState;
std::vector<int> Input::keyboardInputState;
shared_ptr<GLFWwindow> Input::window;
int Input::nKeys;
int Input::nMouseButtons;
glm::vec2 Input::lastMousePos;
glm::vec2 Input::mousePos;
std::array<int, 8> Input::oldMouseInputState;
std::array<int, 8> Input::mouseInputState;

bool Input::getKeyPressed( int keyCode)
{
	return !oldKeyboardInputState[keyCode] && keyboardInputState[keyCode];
}
bool Input::getKeyReleased( int keyCode)
{
	return oldKeyboardInputState[keyCode] && !keyboardInputState[keyCode];
}
bool Input::getKey( int keyCode)
{
	return keyboardInputState[keyCode];
}

bool Input::getMouseButtonPressed(int keyCode)
{
	return !oldMouseInputState[keyCode] && mouseInputState[keyCode];
}
bool Input::getMouseButtonReleased(int keyCode)
{
	return oldMouseInputState[keyCode] && !mouseInputState[keyCode];
}
bool Input::getMouseButton(int keyCode)
{
	return mouseInputState[keyCode];
}

void Input::updateInputState()
{
	std::copy(std::begin(keyboardInputState), std::end(keyboardInputState), std::begin(oldKeyboardInputState));

	for (int i = 0; i < nKeys; i++)
	{
		keyboardInputState[i] = glfwGetKey(window.get(), i);
	}

	std::copy(std::begin(mouseInputState), std::end(mouseInputState), std::begin(oldMouseInputState));

	for (int i = 0; i < nMouseButtons; i++)
	{
		mouseInputState[i] = glfwGetMouseButton(window.get(), i);
	}


	lastMousePos = mousePos;

	double x, y;

	glfwGetCursorPos(window.get(), &x, &y);

	mousePos = glm::vec2(x, y);

}