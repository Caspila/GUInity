#include "EditorCameraControl.h"
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
		//mouseDelta = glm::normalize(mouseDelta);

		glm::vec3 eulerAngles = glm::eulerAngles(getActor()->transform->getRotationQuat());

		eulerAngles = glm::vec3(eulerAngles.x + mouseDelta.y * deltaSeconds * rotationSpeed, eulerAngles.y + mouseDelta.x * deltaSeconds * rotationSpeed, eulerAngles.z);

		//eulerAngles.x = fmodf(eulerAngles.x, 3.1416);
		//eulerAngles.y = fmodf(eulerAngles.y, 3.1416);
		//eulerAngles.z = fmodf(eulerAngles.z, 3.1416);

		cout <<"eulerAngles: " << eulerAngles * Math::Radian2Deg<< endl;

		glm::quat rot = glm::quat(eulerAngles);

		//cout << "quat: " << rot << endl;

		getActor()->transform->setRotationQuat(rot);

		//glm::quat rightQuat = Math::LookAt(getActor()->transform->getRight());
		//glm::quat upQuat = Math::LookAt(getActor()->transform->getUp());
		//
		//getActor()->transform->setRotationQuat(glm::slerp())

		//transform->setRotationQuat()
	}

}