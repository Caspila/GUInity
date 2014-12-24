#pragma once

#include "Module.hpp"
#include <vector>
#include <glm/common.hpp>

#include <array>

class Input
{
	public:

		static std::vector<int> oldKeyboardInputState;
		static std::vector<int> keyboardInputState;

		
		static std::array<int,8> oldMouseInputState;
		static std::array<int,8> mouseInputState;

		static shared_ptr<GLFWwindow> window;

		//void setWindow(shared_ptr<GLFWwindow> window);

		/*void updateKeyboardState(GLFWwindow* window);

		bool getKeyPressed(GLFWwindow* window,int keyCode);
		bool getKeyReleased(GLFWwindow* window, int keyCode);
		bool getKey(GLFWwindow* window, int keyCode);*/

		static void updateInputState();

		static bool getKeyPressed( int keyCode);
		static bool getKeyReleased(int keyCode);
		static bool getKey(int keyCode);
		static bool getMouseButtonPressed(int keyCode);
		static bool getMouseButtonReleased(int keyCode);
		static bool getMouseButton(int keyCode);



		static glm::vec2 lastMousePos;
		static glm::vec2 mousePos;


		~Input() { };
		Input(shared_ptr<GLFWwindow> w) {
			nKeys = 300;
			nMouseButtons = 8;
			window = w; 
			oldKeyboardInputState = std::vector<int>(nKeys, 0);
			keyboardInputState = std::vector<int>(nKeys, 0);
		};                   // Constructor? (the {} brackets) are needed here.


	private:
		// Dont forget to declare these two. You want to make sure they
		// are unaccessable otherwise you may accidently get copies of
		// your singleton appearing.
		Input(Input const&);              // Don't Implement
		void operator=(Input const&); // Don't implement

		static int nMouseButtons;
		static int nKeys;
};
