#include "World.hpp"
#include "Actor.hpp"
#include "Light.hpp"

//std::vector<shared_ptr<Light>> World::lights;
//std::vector<shared_ptr<Actor>> World::actors;

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

shared_ptr<Actor> World::findActor(string name)
{
	for (auto& a : actors)
	{
		if (a->name.compare(name) == 0)
			return a;
		//a->awake();
	}

	return nullptr;
}

void World::awake()
{
	for (auto& a : actors)
	{
		a->awake();
	}
}

void World::tick(float deltaTime)
{
	for (auto& a : actors)
	{
		a->tick(deltaTime);
	}
}