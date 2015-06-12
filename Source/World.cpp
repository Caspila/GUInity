#include "World.hpp"
#include "Actor.hpp"
#include "Light.hpp"
#include "MeshRenderer.hpp"
#include "Factory.hpp"
#include "Physics.hpp"
#include "RigidBody.hpp"
#include "RigidStatic.hpp"
#include "FontMesh.hpp"
#include "EditorCollider.hpp"

//#define _ITERATOR_DEBUG_LEVEL 1

//std::vector<shared_ptr<Light>> World::lights;
//std::vector<shared_ptr<Actor>> World::actors;
//std::vector<shared_ptr<MeshRenderer>> World::meshRenderers;
//std::vector<shared_ptr<Camera>> World::cameras;

World::World()
{
	isAwake = false;
}

void World::init()
{
	physicsScene = Physics::createPhysicsScene();

}

void World::registerObserverAsGame()
{
	isEditor = false;

	Camera::addObserver(shared_from_this());
	Light::addObserver(shared_from_this());
	RigidBody::addObserver(shared_from_this());
	RigidStatic::addObserver(shared_from_this());
	MeshRenderer::addObserver(shared_from_this());
	//FontRenderer::addObserver(shared_from_this());
	Factory::addObserver(shared_from_this());
}


void World::registerObserverAsEditor()
{
	isEditor = true;

	Factory::addObserver(shared_from_this());

	RigidBody::addObserver(shared_from_this());
	RigidStatic::addObserver(shared_from_this());
	EditorCollider::addObserver(shared_from_this());
}

World::~World()
{

}

void World::addMeshRenderer(shared_ptr<MeshRenderer> renderer)
{
	meshRenderers.push_back(renderer);
}
void World::removeMeshRenderer(shared_ptr<MeshRenderer> renderer)
{
    auto it = find(meshRenderers.begin(),meshRenderers.end(),renderer);
    
    if(it!=meshRenderers.end())
    {
        meshRenderers.erase(it);
    }
}

void World::addCamera(shared_ptr<Camera> camera)
{
	cameras.push_back(camera);
}
void World::removeCamera(shared_ptr<Camera> camera)
{
    auto it = find(cameras.begin(),cameras.end(),camera);
    
    if(it!=cameras.end())
    {
        cameras.erase(it);
    }
}

void World::addLight(shared_ptr<Light> light)
{
	lights.push_back(light);
}
void World::removeLight(shared_ptr<Light> light)
{
    auto it = find(lights.begin(),lights.end(),light);
    
    if(it!=lights.end())
    {
        lights.erase(it);
    }
}

void World::addActor(shared_ptr<Actor> actor)
{
	actors.push_back(actor);
}
void World::removeActor(shared_ptr<Actor> actor)
{
    
	auto index = find(actors.begin(), actors.end(), actor);
    
	if (index != actors.end())
    {
        actor->destroyComponents();
		actors.erase(index);
    }
    
}

void World::removeActorDelayed(shared_ptr<Actor> actor)
{
    toRemoveActors.push_back(actor);
}




void World::transferNewActors()
{
	for (auto& a : newActors)
	{
		a->awake();
	}
	std::move(newActors.begin(), newActors.end(),std::back_inserter(actors));
	//for (auto& a : newActors)
	//{
	//	a = nullptr;
	//}
	

	newActors.erase(newActors.begin(),newActors.end());
	
}

void World::addActorDelayed(shared_ptr<Actor> actor)
{
	newActors.push_back(actor);
}




void World::removeDestroyedActors()
{
    for (auto& actor: toRemoveActors)
    {
        shared_ptr<Actor> actorLock = actor.lock();
        
        if(actorLock)
            removeActor(actorLock);
    }
    
  	toRemoveActors.erase(toRemoveActors.begin(),toRemoveActors.end());
    
}

shared_ptr<Actor> World::findActor(string name)
{

	for (auto& a : actors)
	{
		if (a->name.compare(name) == 0)
			return a;
	
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
//	isAwake = false;
//	for (auto& a : actors)
//	{
//		a->awake();
//	}
//	isAwake = true;

    awake(0,actors.size());
    
    isAwake = true;
    
}

void World::awake(unsigned long start, unsigned long end)
{
    if(start == end)
        return;
    
    for(unsigned long i = start; i < end; i++)
    {
        actors[i]->awake();
    }

    awake(end,actors.size());
}

void World::tick(float deltaTime)
{
	for (auto& a : actors)
	{
		a->tick(deltaTime);
	}

	transferNewActors();
    removeDestroyedActors();

//	Physics::tickScene(physicsScene);
}

void World::shutdown()
{

	//cout << "Destroying World" << endl;
	//Camera::removeObserver(shared_from_this());
	//Light::removeObserver(shared_from_this());
	//MeshRenderer::removeObserver(shared_from_this());

	for (auto& x : lights)
		x = nullptr;
	for (auto& x : meshRenderers)
		x = nullptr;
	for (auto& x : cameras)
		x = nullptr;
	for (auto& x : actors)
		x = nullptr;
	for (auto& x : newActors)
		x = nullptr;

}

void World::onNotify(ComponentEventType type, shared_ptr<Component> component, bool isEditor)
{
	if (this->isEditor != isEditor)
		return;

	switch (type)
	{
	case NewMeshRenderer:
		addMeshRenderer(dynamic_pointer_cast<MeshRenderer>(component));
		break;
	case NewCamera:
		addCamera(dynamic_pointer_cast<Camera>(component));
		break;
	case NewLight:
		addLight(dynamic_pointer_cast<Light>(component));
		break;
	case NewRigidBody:
	{
		shared_ptr<RigidBody> rigidBody = dynamic_pointer_cast<RigidBody>(component);
		physicsScene->addActor(*rigidBody->getRigidbody());
		break;
	}
	case NewRigidStatic:
	{
		shared_ptr<RigidStatic> rigidStatic = dynamic_pointer_cast<RigidStatic>(component);
		if (rigidStatic)
			physicsScene->addActor(*rigidStatic->getRigidDynamic());
		break;
	}
	case NewEditorCollider:
	{
		shared_ptr<EditorCollider> editorCollider = dynamic_pointer_cast<EditorCollider>(component);
		if (editorCollider)
			physicsScene->addActor(*editorCollider->getRigidStatic());
		break;
	}
        case RemovedMeshRenderer:
        {
            shared_ptr<MeshRenderer> meshRenderer = dynamic_pointer_cast<MeshRenderer>(component);
            if (meshRenderer)
                removeMeshRenderer(meshRenderer);
            break;
        }
        case RemovedCamera:
        {
            shared_ptr<Camera> camera = dynamic_pointer_cast<Camera>(component);
            if (camera)
                removeCamera(camera);
            break;
        }
        case RemovedLight:
        {
            shared_ptr<Light> light = dynamic_pointer_cast<Light>(component);
            if (light)
                removeLight(light);
            break;
        }
            
		break;
	default:
		break;
	}
}

void World::onNotify(ActorEventType type, shared_ptr<Actor> actor, bool isEditor)
{
    if (this->isEditor != isEditor)
        return;
	
    switch (type)
	{
        case NewActor:
            if(isAwake)
                addActorDelayed(actor);
            else
                addActor(actor);
            break;
        case RemovedActor:
            if(isAwake)
                removeActorDelayed(actor);
            else
                removeActor(actor);
        default:
            break;
	}
    
    

    
//	if (this->isEditor != isEditor)
//		return;
//
//	switch (type)
//	{
//	case NewActor:
//		if (isAwake)
//			addActor(actor);
//		else
//			addActorDelayed(actor);
//		break;
//	default:
//		break;
//	}
}