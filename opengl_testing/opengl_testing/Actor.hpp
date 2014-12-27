#pragma once

#include "Module.hpp"
#include <vector>
#include "ScriptComponent.hpp"
#include "Transform.hpp"
#include "RigidBody.hpp"

class Actor;
class MeshRenderer;

//class Transform;
//class ScriptComponent;

class Actor : public std::enable_shared_from_this<Actor>
#ifdef GUINITY_DEBUG
, public StaticCounter<Actor>
#endif
{


public:
	Actor(string name);// , shared_ptr<MeshRenderer> meshRenderer);
	virtual ~Actor();

	string name;
	shared_ptr<Transform> transform;
	//shared_ptr<MeshRenderer> meshRenderer;

	//vector<shared_ptr<ScriptComponent>> scriptComponents;
	vector<shared_ptr<Component>> components;

	void awake();
	void tick(float deltaSeconds) ;

	void triggerPhysxCollision(Actor* actor);
	void triggerPhysxTrigger(Actor* actor);


	weak_ptr<Actor> parent;
	vector<weak_ptr<Actor>> children;

	void setParent(shared_ptr<Actor> parent);
	void addChildren(shared_ptr<Actor> children);


	void setActive(bool isActive);

	bool isActive;

	template <typename T>
	shared_ptr<T> AddComponent()
	{
		shared_ptr<T> component = make_shared<T>();
		component->setActor(transform->actor);
		components.push_back(component);
		component->init();

//		std::cout << has_serialize<T, int(const std::string&)>::value; // will print 1

		return component;
	}

	template <typename T>
	shared_ptr<T> GetComponent()
	{
		for (auto& x : components)
		{
			shared_ptr<T> wantedComponent = dynamic_pointer_cast<T> (x);

			if (wantedComponent)
				return wantedComponent;
		}

		return nullptr;
	}
/*
	shared_ptr<RigidBody> GetComponent()
	{
		for (auto& x : components)
		{
			shared_ptr<RigidBody> wantedComponent = dynamic_pointer_cast<RigidBody> (x);

			if (wantedComponent)
				return wantedComponent;
		}

		return nullptr;
	}*/
};

//template <typename T>
//shared_ptr<T> AddScript(shared_ptr<Actor> actor)
//{
//	shared_ptr<T> script = make_shared<T>();
//
//	actor->scriptComponents.push_back(ScriptComponent(actor, script));
//
//	return script;
//}