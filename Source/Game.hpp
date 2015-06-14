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

	static shared_ptr<World> world;
};

