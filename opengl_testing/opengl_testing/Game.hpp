#pragma once

#include "Module.hpp"
#include <PxPhysics.h>
#include "World.hpp"
#include "Observer.hpp"

using namespace physx;

class Camera;

class Game : public Observer, public enable_shared_from_this<Game>
{
public:
	Game();
	~Game();

	void update(shared_ptr<World> world, float deltaSeconds);

	PxScene* physicsScene;


	void init();
	void shutdown();

	virtual void onNotify(EventType type, shared_ptr<Component> component) override;
	//shared_ptr<Camera> camera;

	//vector<Actor> ctors;
};

