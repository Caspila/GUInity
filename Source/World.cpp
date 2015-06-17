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

/** Default Constructor */
World::World()
: isAwake(false)
{
    
}
/** Initializes the physics scene */
void World::init()
{
	physicsScene = Physics::createPhysicsScene();
}

/** Releases any alocated memory */
void World::shutdown()
{
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

/** Adds a MeshRenderer to the meshRenderers vector
 @param[in] meshRenderer The MeshRenderer to be added*/
void World::addMeshRenderer(shared_ptr<MeshRenderer> renderer)
{
	meshRenderers.push_back(renderer);
}

/** Removes a MeshRenderer from the meshRenderers vector
 @param[in] meshRenderer The MeshRenderer to be removed */
void World::removeMeshRenderer(shared_ptr<MeshRenderer> renderer)
{
    auto it = find(meshRenderers.begin(),meshRenderers.end(),renderer);
    
    if(it!=meshRenderers.end())
    {
        meshRenderers.erase(it);
    }
}

/** Adds a Camera to the cameras vector
 @param[in] camera The Camera to be added*/
void World::addCamera(shared_ptr<Camera> camera)
{
	cameras.push_back(camera);
}

/** Removes a Camera from the cameras vector
 @param[in] camera The Camera to be removed*/
void World::removeCamera(shared_ptr<Camera> camera)
{
    auto it = find(cameras.begin(),cameras.end(),camera);
    
    if(it!=cameras.end())
    {
        cameras.erase(it);
    }
}

/** Adds a Light to the lights vector
 @param[in] light The Light to be added*/
void World::addLight(shared_ptr<Light> light)
{
	lights.push_back(light);
}

/** Removes a Light from the lights vector
 @param[in] light The Light to be removed*/
void World::removeLight(shared_ptr<Light> light)
{
    auto it = find(lights.begin(),lights.end(),light);
    
    if(it!=lights.end())
    {
        lights.erase(it);
    }
}

/** Adds an Actor to the world
 @param[in] actor The Actor to be added*/
void World::addActor(shared_ptr<Actor> actor)
{
	actors.push_back(actor);
}
/** Adds an Actor to the world in the next "tick" loop
 @param[in] actor The Actor to be added*/
void World::addActorDelayed(shared_ptr<Actor> actor)
{
	newActors.push_back(actor);
}
/** Awakes the actors that were added with delay and move them to the actors vector  */
void World::transferNewActors()
{
	for (auto& a : newActors)
	{
		a->awake();
	}
	std::move(newActors.begin(), newActors.end(),std::back_inserter(actors));
    
    
	newActors.erase(newActors.begin(),newActors.end());
	
}



/** Removes an Actor from the world
 @param[in] actor The Actor to be removed*/
void World::removeActor(shared_ptr<Actor> actor)
{
    
	auto index = find(actors.begin(), actors.end(), actor);
    
	if (index != actors.end())
    {
        actor->destroyComponents();
		actors.erase(index);
    }
    
}
/** Removes an Actor from the world in the next "tick" loop"
 @param[in] actor The Actor to be removed*/
void World::removeActorDelayed(shared_ptr<Actor> actor)
{
    toRemoveActors.push_back(actor);
}

/** Removes the actors that were marked to be removed with delay */
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

/** Finds an Actor in the World given a name
 @param[in] name The name of the Actor to be found. Returns the first one that matches the name or nullptr in case none was found */
shared_ptr<Actor> World::findActor(string name)
{
    
	for (auto& a : actors)
	{
		if (a->name.compare(name) == 0)
			return a;
        
	}
    
	return nullptr;
}

/** Awakes the World and every Actor in it */
void World::awake()
{
    
    awake(0,actors.size());
    
    isAwake = true;
    
}

/** Awakes a range of Actors in the world */
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

/** Ticks the World and every Actor in it */
void World::tick(float deltaTime)
{
	transferNewActors();
    removeDestroyedActors();
	
    for (auto& a : actors)
	{
		a->tick(deltaTime);
	}
    
    
}

/** Register the World to as Observers to Subjects that are important for the Game */
void World::registerObserverAsGame()
{
	isEditor = false;
    
	Camera::addObserver(shared_from_this());
	Light::addObserver(shared_from_this());
	RigidBody::addObserver(shared_from_this());
	RigidStatic::addObserver(shared_from_this());
	MeshRenderer::addObserver(shared_from_this());
	Factory::addObserver(shared_from_this());
}

/** Register the World to as Observers to Subjects that are important for the Editor */
void World::registerObserverAsEditor()
{
	isEditor = true;
    
	Factory::addObserver(shared_from_this());
    
	RigidBody::addObserver(shared_from_this());
	RigidStatic::addObserver(shared_from_this());
    MeshRenderer::addObserver(shared_from_this());
	EditorCollider::addObserver(shared_from_this());
}


/** Receive Component notifications from Subjects that this World is observing */
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

/** Receive Actor notifications from Subjects that this World is observing */
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
    
}