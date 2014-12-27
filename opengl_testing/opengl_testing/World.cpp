#include "World.hpp"
#include "Actor.hpp"
#include "Light.hpp"
#include "MeshRenderer.hpp"

std::vector<shared_ptr<Light>> World::lights;
std::vector<shared_ptr<Actor>> World::actors;
std::vector<shared_ptr<MeshRenderer>> World::meshRenderers;
std::vector<shared_ptr<Camera>> World::cameras;

World::World()
{

}

void World::init()
{
	shared_ptr<World> thisPtr = shared_from_this();
	Camera::addObserver(shared_from_this());
	Light::addObserver(shared_from_this());
	MeshRenderer::addObserver(shared_from_this());
}



	World::~World()
	{

	}

void World::addMeshRenderer(shared_ptr<MeshRenderer> renderer)
{
	meshRenderers.push_back(renderer);
}

void World::addCamera(shared_ptr<Camera> camera)
{
	cameras.push_back(camera);
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
shared_ptr<Actor> World::getSharedPtrActor(Actor* actor)
{
	for (auto& a : actors)
	{
		if (a.get() == actor)
			return a;
	}
	cerr << "There's a pointer to an actor that does not live in the world!" << endl;	

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

void World::shutdown()
{

	//cout << "Destroying World" << endl;
	//Camera::removeObserver(shared_from_this());
	//Light::removeObserver(shared_from_this());
	//MeshRenderer::removeObserver(shared_from_this());

	//for (auto& x : lights)
	//	x.reset();
	for (auto& x : lights)
		x = nullptr;
	for (auto& x : meshRenderers)
		x = nullptr;
	for (auto& x : cameras)
		x = nullptr;
	for (auto& x : actors)
		x = nullptr;

}

void World::onNotify(EventType type, shared_ptr<Component> component)
{
	switch (type)
	{
	case NewMeshRenderer:
		World::addMeshRenderer(dynamic_pointer_cast<MeshRenderer>(component));
		break;
	case NewCamera:
		World::addCamera(dynamic_pointer_cast<Camera>(component));
		break;
	case NewLight:
		World::addLight(dynamic_pointer_cast<Light>(component));
		break;
	default:
		break;
	}
}