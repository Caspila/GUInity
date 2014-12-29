#pragma once

#include "Module.hpp"
#include <PxPhysics.h>
#include "World.hpp"
#include "Observer.hpp"

using namespace physx;

class Camera;

class Game : public enable_shared_from_this<Game>
{
public:
	Game();
	~Game();

	void update(float deltaSeconds);

	PxScene* physicsScene;


	void init();
	void shutdown();

	//virtual void onNotify(EventType type, shared_ptr<Component> component, bool isEditor) override;

	static shared_ptr<World> world;


	//shared_ptr<Camera> camera;

	//vector<Actor> ctors;
};

