#pragma once

#include <vector>
#include "Actor.hpp"
#include "Light.hpp"

//class Light;
//class Actor;

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
	shared_ptr<Actor> findActor(string name);
	void awake();
	void tick(float deltaTime);
};

