#include "MoveHandle.hpp"
#include "Input.hpp"
#include "Physics.hpp"
#include "Editor.hpp"
#include "print.hpp"
#include "Transform.hpp"

MoveHandle::MoveHandle()
{
}


MoveHandle::~MoveHandle()
{
}


void MoveHandle::setAxis(MoveAxis axis)
{
	this->axis = axis;
}

void MoveHandle::tick(float deltaSeconds)
{
	shared_ptr<Actor> currentActor = Editor::currentSelectedActor;
	if (!currentActor)
		return;
//
//	shared_ptr<Actor> myParent = getActor()->getParent();
//	if (myParent)
//	{
//		myParent->transform->position = currentActor->transform->position;
//		myParent->transform->rotationQuat = currentActor->transform->rotationQuat;
//	}

	Ray r = Editor::cameraComponent->screenPointToRay(Input::mousePos);

	PxRaycastBuffer hitCallback;


	if (Input::getMouseButtonPressed(GLFW_MOUSE_BUTTON_1) && Physics::rayCast(Editor::world->physicsScene, r, 300, hitCallback))
	{
		Actor *a = (Actor*)hitCallback.block.actor->userData;

		if (a == getActor().get())
		{
            cout << a->name << endl;
			isPressed = true;
		}
	}
	else if (Input::getMouseButtonReleased(GLFW_MOUSE_BUTTON_1))
		isPressed = false;

	if (isPressed)
	{

		glm::vec2 mouseDelta = Input::mouseDelta;
		if (glm::length(mouseDelta) > 0)
		{
			glm::vec3 newWorldPos = Editor::cameraComponent->screenPointToWorld(Input::mousePos);
			glm::vec3 oldWorldPos = Editor::cameraComponent->screenPointToWorld(Input::mousePos - Input::mouseDelta);

			glm::vec3 mouseWorldDir = newWorldPos - oldWorldPos;
			mouseWorldDir = glm::normalize(mouseWorldDir);

			//cout << "new: " << oldWorldPos << endl;
			//cout << "old: " << newWorldPos << endl;

			//cout << "mouseWorldDir: " << mouseWorldDir << endl;

			glm::vec3 dirAxis;

			switch (axis)
			{
			case MoveAxis::up:
				dirAxis = currentActor->transform->getUp();
				break;
			case MoveAxis::right:
				dirAxis = currentActor->transform->getRight();
				break;
			case MoveAxis::forward:
				dirAxis = currentActor->transform->getForward();
				break;
			default:
				break;
			}


			//cout << "dirAxis: " << dirAxis << endl;

			glm::vec3 delta = dirAxis * glm::dot(mouseWorldDir, dirAxis) * 0.1f;

			//cout << "dotDekta: " << delta << endl;

			cout << "Mouse click on ME!" << getActor()->name << endl;

			//if (mouseDelta.x > 0)
			//	cout << "Move" << endl;
			currentActor->transform->position = currentActor->transform->position + delta;
		}
		//getActor()->transform->position = getActor()->transform->position + axis;
	}
}
