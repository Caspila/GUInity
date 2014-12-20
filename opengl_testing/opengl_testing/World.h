#pragma once

#include <vector>
#include "Actor.h"
#include "Light.h"

class World
{
public:
	World();
	~World();

	std::vector<shared_ptr<Light>> lights;

	void addLight(shared_ptr<Light> light);

	std::vector<shared_ptr<Actor>> actors;

	void addActor(shared_ptr<Actor> actor);
	void removeActor(shared_ptr<Actor> actor);

	void tick(float deltaTime);
};

