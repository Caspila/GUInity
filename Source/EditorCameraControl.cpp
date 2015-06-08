#include "EditorCameraControl.hpp"
#include "Input.hpp"
#include "Actor.hpp"
#include "Transform.hpp"
#include "print.hpp"

EditorCameraControl::EditorCameraControl()
{
}


EditorCameraControl::~EditorCameraControl()
{
}

void EditorCameraControl::init()
{
	moveSpeed = 5;
	rotationSpeed = 1;
}

void EditorCameraControl::tick(float deltaSeconds)
{
	shared_ptr<Actor> actor = getActor();
	shared_ptr<Transform> transform = actor->transform;

	if (Input::getKey(GLFW_KEY_W))
	{
		glm::vec3 pos = transform->position;

		pos += transform->getForward() * moveSpeed * deltaSeconds;

		transform->setPosition(pos);
	}

	if (Input::getKey(GLFW_KEY_S))
	{
		glm::vec3 pos = transform->position;

		pos -= transform->getForward()* moveSpeed * deltaSeconds;

		transform->setPosition(pos);
	}


	if (Input::getKey(GLFW_KEY_D))
	{
		glm::vec3 pos = transform->position;

		pos -= transform->getRight()* moveSpeed * deltaSeconds;

		transform->setPosition(pos);
	}



	if (Input::getKey(GLFW_KEY_A))
	{
		glm::vec3 pos = transform->position;

		pos += transform->getRight()* moveSpeed * deltaSeconds;

		transform->setPosition(pos);
	}

	bool rightButtonPressed = Input::getMouseButton(GLFW_MOUSE_BUTTON_2);

	if (rightButtonPressed)
	{
		glm::vec2 mouseDelta = Input::mouseDelta;

		getActor()->transform->rotation = glm::angleAxis(-mouseDelta.x * deltaSeconds, glm::vec3(0, 1, 0))* glm::angleAxis(mouseDelta.y * deltaSeconds, getActor()->transform->getRight())  * getActor()->transform->rotation;

	}

}