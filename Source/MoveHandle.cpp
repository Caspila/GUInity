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

	Ray r = Editor::cameraComponent->screenPointToRay(Input::getMousePos());

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

		glm::vec2 mouseDelta = Input::getMouseDelta();
		if (glm::length(mouseDelta) > 0)
		{
			glm::vec3 newWorldPos = Editor::cameraComponent->screenPointToWorld(Input::getMousePos());
			glm::vec3 oldWorldPos = Editor::cameraComponent->screenPointToWorld(Input::getMousePos() - Input::getMouseDelta());

			glm::vec3 mouseWorldDir = newWorldPos - oldWorldPos;
			mouseWorldDir = glm::normalize(mouseWorldDir);

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

			glm::vec3 delta = dirAxis * glm::dot(mouseWorldDir, dirAxis) * 0.1f;


			cout << "Mouse click on ME!" << getActor()->name << endl;

			currentActor->transform->position = currentActor->transform->position + delta;
		}
	}
}
