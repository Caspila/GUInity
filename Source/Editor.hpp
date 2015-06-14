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
class UIWidget;

class Editor : public enable_shared_from_this<Editor>
{
public:
	Editor();
	~Editor();

	static void init();
	static void shutdown();

	static void update(float deltaSeconds, shared_ptr<World> gameWorld);

	static shared_ptr<Actor> cameraActor;
	static shared_ptr<Camera> cameraComponent;

	static shared_ptr<World> world;

	static shared_ptr<Actor> currentSelectedActor;

	static shared_ptr<Actor> moveHandles;
	static shared_ptr<Actor> rotateHandles;
    static shared_ptr<Actor> scaleHandles;
    
    static shared_ptr<UIWidget> uiWidgetTest;
    
    static TransformMode transformMode;
};

