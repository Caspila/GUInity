#include "RotateHandle.hpp"
#include "Input.hpp"
#include "Physics.hpp"
#include "Editor.hpp"
#include "print.hpp"
#include "CapsuleCollider.hpp"
#include "Math.hpp"

RotateHandle::RotateHandle()
{
}


RotateHandle::~RotateHandle()
{
}

void RotateHandle::setAxis(RotateAxis axis)
{
	this->axis = axis;

	switch (axis)
	{
        case RotateAxis::x:
		rotationAxis = glm::vec3(1, 0, 0);
		break;
        case RotateAxis::y:
		rotationAxis = glm::vec3(0, 1, 0);
		break;
        case RotateAxis::z:
		rotationAxis = glm::vec3(0, 0, 1);
		break;
	default:
		break;
	}
}

void RotateHandle::awake()
{
	lastDot = 0;
}

void RotateHandle::tick(float deltaSeconds)
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


	if (Input::getMouseButtonPressed(GLFW_MOUSE_BUTTON_1) && Physics::rayCast(Editor::world->physicsScene, r, 300, hitCallback))
	{
		Actor *a = (Actor*)hitCallback.block.actor->userData;

		if (a == getActor().get())
		{
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
			glm::vec3 point1 = currentActor->transform->position;
			glm::vec3 point2 = point1 + currentActor->transform->getUp();
			glm::vec3 point3 = point1 + currentActor->transform->getRight();

			Plane p(point1, point2, point3);

			glm::vec3 newWorldPos = Editor::cameraComponent->screenPointToWorld(Input::mousePos);
			glm::vec3 oldWorldPos = Editor::cameraComponent->screenPointToWorld(Input::mousePos - Input::mouseDelta);

			glm::vec3 newWorldProj = projectOnPlane(newWorldPos - point1, p);
			glm::vec3 oldWorldProj = projectOnPlane(oldWorldPos - point1, p);

			glm::vec3 mouseWorldDir = newWorldPos - oldWorldPos;
			mouseWorldDir = glm::normalize(mouseWorldDir);

			//cout << "newWorldProj" << newWorldProj << endl;
			//cout << "oldWorldProj" << oldWorldProj << endl;

			//float dot = glm::dot(newWorldPos, oldWorldPos);
			//float dot = glm::dot(newWorldProj, oldWorldProj);

			glm::vec3 dirAxis;

			switch (axis)
			{
			case RotateAxis::z:
				dirAxis = currentActor->transform->getUp();
				break;
			case RotateAxis::y:
				dirAxis = currentActor->transform->getForward();
				break;
			case RotateAxis::x:
				dirAxis = currentActor->transform->getRight();
				break;
			default:
				break;
			}

			float dot = glm::dot(mouseWorldDir, dirAxis);
//			cout <<"Dot" << dot - lastDot << endl;

			//cout << "Dot" << dot << endl;
//			cout << "lastDot" << lastDot << endl;

			glm::vec3 eulerAngles = glm::eulerAngles(currentActor->transform->rotationQuat);
			
			//cout << "eulerAngles.z" << eulerAngles.z << endl;
			
			//
			//eulerAngles.z += (dot - lastDot) * 100 * deltaSeconds;
			//
			//float f = Math::sgn(dot - lastDot);
			float f = sgn(dot);
			cout << "f" << f << endl;

			currentActor->transform->rotationQuat = glm::angleAxis(f * deltaSeconds, rotationAxis) * currentActor->transform->rotationQuat;


			lastDot = dot;

			//cout << 


			//glm::vec3 mouseWorldDir = newWorldPos - oldWorldPos;
			//mouseWorldDir = glm::normalize(mouseWorldDir);

			////cout << "new: " << oldWorldPos << endl;
			////cout << "old: " << newWorldPos << endl;

			////cout << "mouseWorldDir: " << mouseWorldDir << endl;

			//glm::vec3 dirAxis;

			//switch (axis)
			//{
			//case RotateAxis::x:
			//	dirAxis = currentActor->transform->getUp();
			//	break;
			//case RotateAxis::y:
			//	dirAxis = currentActor->transform->getRight();
			//	break;
			//case RotateAxis::z:
			//	dirAxis = currentActor->transform->getForward();
			//	break;
			//default:
			//	break;
			//}


			////cout << "dirAxis: " << dirAxis << endl;

			//glm::vec3 delta = dirAxis * glm::dot(mouseWorldDir, dirAxis) * 0.1f;

			//cout << "dotDekta: " << delta << endl;

			////cout << "Mouse click on ME!" << getActor()->name << endl;

			////if (mouseDelta.x > 0)
			////	cout << "Move" << endl;
			//currentActor->transform->position = currentActor->transform->position + delta;

		}
		//getActor()->transform->position = getActor()->transform->position + axis;
	}
}
