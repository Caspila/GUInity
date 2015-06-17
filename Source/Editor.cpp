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


/** The Editor Camera Actor */
shared_ptr<Actor> Editor::cameraActor;
/** The Editor Camera Component */
shared_ptr<Camera> Editor::cameraComponent;
/** The current selected actor */
shared_ptr<Actor> Editor::currentSelectedActor;
/** The Move handles to translate Actors */
shared_ptr<Actor> Editor::moveHandles;
/** The Rotate handles to rotate Actors */
shared_ptr<Actor> Editor::rotateHandles;
/** The Scale handles to scale Actors */
shared_ptr<Actor> Editor::scaleHandles;
/** The Editor World */
shared_ptr<World> Editor::world;
/** The current transform mode: Move/Rotate/Scale */
TransformMode Editor::transformMode;


/** Initalize the editor. Creates the Scene camera and the Transform handles to manipulate the Actors */
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

/** Releases any allocated memory */
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

/** "Ticks" the editor. Checks if user clicked on an actor and enable/disable Transform handles. Ticks and Renders the Editor and Game Worlds
 @param[in] deltaSeconds Duration of last frame
 @param[in] gameWorld The Game World
 */
void Editor::update(float deltaSeconds, shared_ptr<World> gameWorld)
{
    // Enables/Disables PhysX Render Debug
    if(Input::getKeyPressed(GLFW_KEY_B))
    {
        Physics::toggleDebugVisualization(world->physicsScene);
    }
    
    // Checks if user is clicking at an object
	Ray r = cameraComponent->screenPointToRay(Input::mousePos);
    
	PxRaycastBuffer hitCallback;
	if (Input::getMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
    {
		if (Physics::rayCast(world->physicsScene, r, 300, hitCallback))
		{
			Actor *a = (Actor*)hitCallback.block.actor->userData;
            
            shared_ptr<Actor> clickedActor = a->shared_from_this();
            
            
			if (clickedActor)
			{
				shared_ptr<EditorCollider> editorCollider = clickedActor->GetComponent<EditorCollider>();
				
				if (editorCollider)
					currentSelectedActor = editorCollider->getGameActor();
                
			}
		}
        else
            currentSelectedActor = nullptr;
    }
    
    // Switches between the three Transform modes
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
    
    
    // Activate the handles if there's an Actor selected
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
    
    // Tick the world
	world->tick(deltaSeconds);
    
    // Tick the physics (Nothing happens cause everything is Query Only), this is purely for getting the render debug
	Physics::tickScene(deltaSeconds,world->physicsScene);
    
	cameraComponent->computeModelViewMatrix();
    
	GraphicsSystem::getInstance()->clear();
    
    // Render the Editor World
	GraphicsSystem::getInstance()->render(cameraComponent, world->meshRenderers, gameWorld->lights);
    
    // Render the Game World
	GraphicsSystem::getInstance()->render(cameraComponent, gameWorld->meshRenderers, gameWorld->lights);
    
    // Render the Physics Debug
	GraphicsSystem::getInstance()->renderPhysicsDebug(cameraComponent, world->physicsScene->getRenderBuffer(), glm::vec4(1, 1, 1,1));
    
	GraphicsSystem::getInstance()->swap();
    
}
