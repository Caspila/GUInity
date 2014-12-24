#pragma once

#include "Module.hpp"
#include <vector>
#include "ScriptComponent.hpp"

class Actor;
class MeshRenderer;
class Transform;
//class ScriptComponent;

class Actor
#ifdef GUINITY_DEBUG
: public StaticCounter<Actor>
#endif
{


public:
	Actor(string name, shared_ptr<MeshRenderer> meshRenderer);
	virtual ~Actor();

	string name;
	shared_ptr<Transform> transform;
	shared_ptr<MeshRenderer> meshRenderer;

	vector<shared_ptr<ScriptComponent>> scriptComponents;

	void awake();
	void tick(float deltaSeconds) ;

	template <typename T>
	shared_ptr<T> AddScript()
	{
		shared_ptr<T> scriptComponent = make_shared<T>();
		scriptComponent->setActor(transform->actor);
		scriptComponents.push_back(scriptComponent);

		return scriptComponent;
	}

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