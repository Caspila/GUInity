#pragma once

#include <PxPhysics.h>
#include "Module.hpp"
#include <vector>
#include "Actor.hpp"
#include "Observer.hpp"
#include "World.hpp"

using namespace physx;

class Camera;
class Actor;

class Editor : public enable_shared_from_this<Editor>
{
public:
    
    /** Initalize the editor. Creates the Scene camera and the Transform handles to manipulate the Actors */
	static void init();
    /** Releases any allocated memory */
	static void shutdown();
    
    /** "Ticks" the editor. Checks if user clicked on an actor and enable/disable Transform handles. Ticks and Renders the Editor and Game Worlds
     @param[in] deltaSeconds Duration of last frame
     @param[in] gameWorld The Game World
     */
	static void update(float deltaSeconds, shared_ptr<World> gameWorld);
    
    /** The Editor Camera Actor */
	static shared_ptr<Actor> cameraActor;
    /** The Editor Camera Component */
	static shared_ptr<Camera> cameraComponent;
    /** The Editor World */
	static shared_ptr<World> world;
    
    /** The current selected actor */
	static shared_ptr<Actor> currentSelectedActor;
    
    /** The Move handles to translate Actors */
	static shared_ptr<Actor> moveHandles;
    /** The Rotate handles to rotate Actors */
	static shared_ptr<Actor> rotateHandles;
    /** The Scale handles to scale Actors */
    static shared_ptr<Actor> scaleHandles;
    
    /** The current transform mode: Move/Rotate/Scale */
    static TransformMode transformMode;
};

