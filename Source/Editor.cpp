#include "Editor.hpp"
#include "Time.hpp"
#include "Physics.hpp"
#include "GraphicsSystem.hpp"
#include "Camera.hpp"
#include "Factory.hpp"
#include "EditorCameraControl.hpp"
#include "Input.hpp"
#include "SphereCollider.hpp"
#include "MoveHandle.hpp"
#include "EditorCollider.hpp"
#include "MoveTool.hpp"
#include "RotateTool.hpp"
#include "Mesh.hpp"
#include "print.hpp"
#include "Math.hpp"
#include "ScaleTool.hpp"

//PxScene* Editor::physicsScene;
shared_ptr<Actor> Editor::cameraActor;
shared_ptr<Camera> Editor::cameraComponent;
shared_ptr<Actor> Editor::currentSelectedActor;
shared_ptr<Actor> Editor::moveHandles;
shared_ptr<Actor> Editor::rotateHandles;
shared_ptr<Actor> Editor::scaleHandles;
shared_ptr<World> Editor::world;
shared_ptr<UIWidget> Editor::uiWidgetTest;
TransformMode Editor::transformMode;
//vector<shared_ptr<Actor>>  Editor::editorActors;

Editor::Editor()
{
}

Editor::~Editor()
{
}

void callBack()
{
    cout << "Button1 pressed!"<< endl;
}

void callBack2()
{
    cout << "Button2 pressed!"<< endl;
}

void Editor::init()
{
    transformMode = TransformMode::none;
    
	world = make_shared<World>();
    
	world->init();
	world->registerObserverAsEditor();
    
	cameraActor = Factory::CreateEditorActor("CameraEditor");
	cameraActor->transform->setPosition(glm::vec3(0, 0, 10));
	cameraActor->transform->setRotation(glm::quat(glm::vec3(0, 180 * Deg2Radian, 0)));
	cameraComponent = cameraActor->AddComponent<Camera>();
	cameraActor->AddComponent<EditorCameraControl>();
    
	moveHandles = Factory::CreateEditorActor("MoveHandles");
	moveHandles->AddComponent<MoveTool>();
    
    moveHandles->setActive(false);
    
    rotateHandles = Factory::CreateEditorActor("RotateHandles");
	rotateHandles->AddComponent<RotateTool>();
    
    rotateHandles->setActive(false);
    
    scaleHandles = Factory::CreateEditorActor("ScaleHandles");
	scaleHandles->AddComponent<ScaleTool>();
    
    scaleHandles->setActive(false);
    
}

void Editor::shutdown()
{
	cameraActor = nullptr;
    
	cameraComponent = nullptr;
	
	currentSelectedActor = nullptr;
	
	moveHandles = nullptr;
    
	scaleHandles = nullptr;
    
	rotateHandles = nullptr;
    
    
    
	world->shutdown();
    
}
void Editor::update(float deltaSeconds, shared_ptr<World> gameWorld)
{
    
    if(Input::getKeyPressed(GLFW_KEY_B))
    {
        Physics::toggleDebugVisualization(world->physicsScene);
    }
    
	Ray r = cameraComponent->screenPointToRay(Input::mousePos);
    
	PxRaycastBuffer hitCallback;
	if (Input::getMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
		if (Physics::rayCast(world->physicsScene, r, 300, hitCallback))
		{
			Actor *a = (Actor*)hitCallback.block.actor->userData;
            
			shared_ptr<Actor> clickedActor = world->getSharedPtrActor(a);
            
			if (clickedActor)
			{
				shared_ptr<EditorCollider> editorCollider = clickedActor->GetComponent<EditorCollider>();
				
				if (editorCollider)
					currentSelectedActor = editorCollider->getGameActor();
                
			}
		}
        else
            currentSelectedActor = nullptr;
    
    
    if(Input::getKeyPressed(GLFW_KEY_Q))
    {
        transformMode = TransformMode::move;
    } else
        if(Input::getKeyPressed(GLFW_KEY_W))
        {
            transformMode = TransformMode::rotate;
        }
        else
            if(Input::getKeyPressed(GLFW_KEY_E))
            {
                transformMode = TransformMode::scale;
            }
    
    
    
    if(currentSelectedActor!=nullptr)
    {
        switch (transformMode) {
            case TransformMode::none:
                rotateHandles->setActive(false);
                moveHandles->setActive(false);
                scaleHandles->setActive(false);
                break;
            case TransformMode::move:
                rotateHandles->setActive(false);
                moveHandles->setActive(true);
                scaleHandles->setActive(false);
                break;
            case TransformMode::rotate:
                rotateHandles->setActive(true);
                moveHandles->setActive(false);
                scaleHandles->setActive(false);
                break;
            case TransformMode::scale:
                rotateHandles->setActive(false);
                moveHandles->setActive(false);
                scaleHandles->setActive(true);
                break;
                
            default:
                break;
        }
    }
    else
    {
        moveHandles->setActive(false);
        rotateHandles->setActive(false);
        scaleHandles->setActive(false);
    }
    
	world->tick(deltaSeconds);
    
	Physics::tickScene(deltaSeconds,world->physicsScene);
	Physics::updateActorsTransform(world->physicsScene);
    
	cameraComponent->computeModelViewMatrix();
    
	GraphicsSystem::getInstance()->clear();
    
	GraphicsSystem::getInstance()->render(cameraComponent, world->meshRenderers, gameWorld->lights);
    
	GraphicsSystem::getInstance()->render(cameraComponent, gameWorld->meshRenderers, gameWorld->lights);
    
	GraphicsSystem::getInstance()->renderPhysicsDebug(cameraComponent, world->physicsScene->getRenderBuffer(), glm::vec4(1, 1, 1,1));
    
	GraphicsSystem::getInstance()->swap();
    
}
