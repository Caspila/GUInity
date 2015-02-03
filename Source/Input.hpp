#pragma once

#include "Module.hpp"
#include <vector>
#include <glm/common.hpp>

#include <array>

class Input
{

private:
	const static int nMouseButtons = 8;
	const static int nKeys = 300;
	static shared_ptr<GLFWwindow> window;

	//static int nMouseButtons;
	//static int nKeys;

	public:
		/** Constructor for a window handle */
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



		/** Returns true if the key was pressed (1st frame only) */
		static bool getKeyPressed( int keyCode);
		/** Returns true if the key was pressed (release frame only) */
		static bool getKeyReleased(int keyCode);
		/** Returns true if the key IS pressed (every frame that the key is pressed) */
		static bool getKey(int keyCode);
	
		/** Returns true if the mouse button was pressed (1st frame only) */
		static bool getMouseButtonPressed(int keyCode);
		/** Returns true if the mouse button was pressed (release frame only) */
		static bool getMouseButtonReleased(int keyCode);
		/** Returns true if the mouse button IS pressed (every frame that the mouse button is pressed) */
		static bool getMouseButton(int keyCode);

		/** Updates the state of input. Swaps the old/new and gets the new input state */
		static void updateInputState();

		/** Last mouse position x,y on screen */
		static glm::vec2 lastMousePos;
		/** Current mouse position x,y on screen */
		static glm::vec2 mousePos;
		/** Mouse position delta, x,y on screen */
		static glm::vec2 mouseDelta;

		/** window getter*/
		static shared_ptr<GLFWwindow> getWindow();
		/** window setter*/
		static void setWindow(shared_ptr<GLFWwindow> window);


};
