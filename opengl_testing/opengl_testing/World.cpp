#include "World.h"


World::World()
{
}


World::~World()
{
	cout << "Destroying World" << endl;
}

void World::addLight(shared_ptr<Light> light)
{
	lights.push_back(light);
}

void World::addActor(shared_ptr<Actor> actor)
{
	actors.push_back(actor);
}
void World::removeActor(shared_ptr<Actor> actor)
{
	//auto index = find(actors.begin, actors.end, actor);

	//if (index != actors.end())
	//	actors.erase(index);

}

void World::tick(float deltaTime)
{
	for (auto& a : actors)
	{
		a->tick(deltaTime);
	}
}