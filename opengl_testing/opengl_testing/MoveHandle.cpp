#include "MoveHandle.h"
#include "Input.hpp"
#include "Physics.hpp"
#include "Editor.hpp"

MoveHandle::MoveHandle()
{
}


MoveHandle::~MoveHandle()
{
}


void MoveHandle::setAxis(glm::vec3 axis)
{
	this->axis = axis;
}

void MoveHandle::tick(float deltaSeconds)
{
	shared_ptr<Actor> currentActor = Editor::currentSelectedActor;
	if (!currentActor)
		return;

	shared_ptr<Actor> myParent = getActor()->getParent();
	if (myParent)
	{
		myParent->transform->position = currentActor->transform->position;
		myParent->transform->rotationQuat = currentActor->transform->rotationQuat;
	}

	Ray r = Editor::cameraComponent->screenPointToRay(Input::mousePos);

	PxRaycastBuffer hitCallback;


	if (Input::getMouseButton(GLFW_MOUSE_BUTTON_1) && Physics::rayCast(r, 300, hitCallback))
	{
		Actor *a = (Actor*)hitCallback.block.actor->userData;

		if (a == getActor().get())
		{
			glm::vec2 mouseDelta = Input::mouseDelta;

			cout << "Mouse click on ME!" << getActor()->name << endl;


			currentActor->transform->position = currentActor->transform->position + axis * 0.1f * mouseDelta.x;

			//getActor()->transform->position = getActor()->transform->position + axis;
		}
			
	}


}