#include "ScaleHandle.hpp"
#include "Input.hpp"
#include "Physics.hpp"
#include "Editor.hpp"
#include "print.hpp"
#include "Math.hpp"

ScaleHandle::ScaleHandle()
{
}


ScaleHandle::~ScaleHandle()
{
}


void ScaleHandle::setAxis(TransformAxis axis)
{
	this->axis = axis;
}

void ScaleHandle::tick(float deltaSeconds)
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
                case TransformAxis::y:
                    //dirAxis = currentActor->transform->getUp();
                    dirAxis = glm::vec3(0,1,0);
                    break;
                case TransformAxis::x:
//                    dirAxis = currentActor->transform->getRight();
                                        dirAxis = glm::vec3(1,0,0);
                    break;
                case TransformAxis::z:
                                                            dirAxis = glm::vec3(0,0,1);
//                    dirAxis = currentActor->transform->getForward();
                    break;
                default:
                    break;
			}
            
            
			//cout << "dirAxis: " << dirAxis << endl;
            
            float signal = sgn(glm::dot(mouseWorldDir, dirAxis));
            
			glm::vec3 delta = dirAxis * 0.1f *  signal;// * glm::dot(mouseWorldDir, dirAxis) * 0.1f;
            
			//cout << "dotDekta: " << delta << endl;
            
//			cout << "Mouse click on ME!" << getActor()->name << endl;
            
			//if (mouseDelta.x > 0)
			//	cout << "Move" << endl;
			currentActor->transform->scale = currentActor->transform->scale + delta;
		}
		//getActor()->transform->position = getActor()->transform->position + axis;
	}
}
