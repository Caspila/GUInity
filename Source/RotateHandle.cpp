#include "RotateHandle.hpp"
#include "Input.hpp"
#include "Physics.hpp"
#include "Editor.hpp"
#include "print.hpp"
#include "CapsuleCollider.hpp"
#include "Math.hpp"
#include "Transform.hpp"
#include "Factory.hpp"

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
		myParent->transform->rotation = currentActor->transform->rotation;
	}

	Ray r = Editor::cameraComponent->screenPointToRay(Input::getMousePos());

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
		glm::vec2 mouseDelta = Input::getMouseDelta();
		if (glm::length(mouseDelta) > 0)
		{
            glm::vec3 point1 = currentActor->transform->position;
            glm::vec3 point2;
            glm::vec3 point3;
           

			glm::vec3 dirAxis;

			switch (axis)
			{
			case RotateAxis::z:
                    point2 = point1 + currentActor->transform->getUp();
                    point3 = point1 + currentActor->transform->getRight();
                    dirAxis = currentActor->transform->getForward();

				break;
			case RotateAxis::y:
                    point2 = point1 + currentActor->transform->getRight();
                    point3 = point1 + currentActor->transform->getForward();
                    
                    dirAxis = currentActor->transform->getUp();

				break;
			case RotateAxis::x:
                    point2 = point1 + currentActor->transform->getUp();
                    point3 = point1 + currentActor->transform->getForward();

				dirAxis = currentActor->transform->getRight();
				break;
			default:
				break;
			}


            
            Plane p(point1, point2, point3);
            
            glm::vec3 newWorldPlane = Editor::cameraComponent->screenPointToPlane(p, Input::getMousePos());
            glm::vec3 oldWorldPlane = Editor::cameraComponent->screenPointToPlane(p, Input::getMousePos() - Input::getMouseDelta());
            
            float dot = 1 - glm::dot((newWorldPlane-point1), (oldWorldPlane-point1));
            dot = fabs(dot);
            
            glm::vec3 cross = glm::cross(newWorldPlane, oldWorldPlane);
            
            int clockwise = -sgn(cross.z);
            
            float rotateAmount = deltaSeconds * 5 * dot;
            if(rotateAmount > 0.1f)
                rotateAmount = 0.1f;
            
            rotateAmount *= clockwise;
            
            currentActor->transform->rotation = glm::angleAxis(rotateAmount, dirAxis) * currentActor->transform->rotation;


		}

	}
}
