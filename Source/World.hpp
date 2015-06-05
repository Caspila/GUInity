#pragma once

#include <vector>
#include "Actor.hpp"
#include "Light.hpp"
#include "Observer.hpp"
#include "Camera.hpp"
//class Light;
//class Actor;

class MeshRenderer;

class World : public Observer, public enable_shared_from_this<World>
		
{
public:

	World();
	~World();
	void init();

	PxScene *physicsScene;

	std::vector<shared_ptr<MeshRenderer>> meshRenderers;
	void addMeshRenderer(shared_ptr<MeshRenderer> meshRenderer);
  	void removeMeshRenderer(shared_ptr<MeshRenderer> meshRenderer);
	
	std::vector<shared_ptr<Camera>> cameras;
	void addCamera(shared_ptr<Camera> camera);
    void removeCamera(shared_ptr<Camera> camera);
	
	std::vector<shared_ptr<Light>> lights;
	void addLight(shared_ptr<Light> light);
   	void removeLight(shared_ptr<Light> light);
	
	std::vector<shared_ptr<Actor>> actors;
    
	void addActor(shared_ptr<Actor> actor);
	void addActorDelayed(shared_ptr<Actor> actor);
	void removeActor(shared_ptr<Actor> actor);
	std::vector<shared_ptr<Actor>> newActors;
	std::vector<weak_ptr<Actor>> toRemoveActors;

	void transferNewActors();
    void removeDestroyedActors();
    
	shared_ptr<Actor> findActor(string name);
	shared_ptr<Actor> getSharedPtrActor(Actor* actor);
	
	bool isAwake;

	void awake();
    void awake(unsigned long start, unsigned long end);
	void tick(float deltaTime);
	void shutdown();

	bool isEditor;

	virtual void onNotify(ComponentEventType type, shared_ptr<Component> component, bool isEditor) override;
	virtual void onNotify(ActorEventType type, shared_ptr<Actor> actor, bool isEditor) override;

	void registerObserverAsGame()  ;
	void registerObserverAsEditor();
};

