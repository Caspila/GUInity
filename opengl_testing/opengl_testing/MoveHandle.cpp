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
	Ray r = Editor::cameraComponent->screenPointToRay(Input::mousePos);

	PxRaycastBuffer hitCallback;


	if (Input::getMouseButton(GLFW_MOUSE_BUTTON_1) && Physics::rayCast(r, 300, hitCallback))
	{
		Actor *a = (Actor*)hitCallback.block.actor->userData;

		if (a == getActor().get())
		{
			cout << "Mouse click on ME!" << getActor()->name << endl;

			shared_ptr<Actor> currentActor = Editor::currentSelectedActor;

			currentActor->transform->position = currentActor->transform->position + axis;

			//getActor()->transform->position = getActor()->transform->position + axis;
		}
			
	}


}