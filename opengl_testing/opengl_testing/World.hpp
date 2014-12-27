#pragma once

#include <vector>
#include "Actor.hpp"
#include "Light.hpp"
#include "Observer.hpp"
#include "Camera.hpp"
//class Light;
//class Actor;

class World : public Observer, public enable_shared_from_this<World>
		
{
public:



	World();
	~World();
	void init();

	static std::vector<shared_ptr<MeshRenderer>> meshRenderers;
	static void addMeshRenderer(shared_ptr<MeshRenderer> meshRenderer);

	static std::vector<shared_ptr<Camera>> cameras;
	static void addCamera(shared_ptr<Camera> camera);
	
	static std::vector<shared_ptr<Light>> lights;
	static void addLight(shared_ptr<Light> light);
	
	static std::vector<shared_ptr<Actor>> actors;
	static void addActor(shared_ptr<Actor> actor);
	static void removeActor(shared_ptr<Actor> actor);
	
	static shared_ptr<Actor> findActor(string name);
	static shared_ptr<Actor> getSharedPtrActor(Actor* actor);

	static void awake();
	static void tick(float deltaTime);
	static void shutdown();

	void onNotify(EventType type, shared_ptr<Component> component);
};

