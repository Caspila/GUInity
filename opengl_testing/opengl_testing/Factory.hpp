#pragma once

#include "Module.hpp"
//#include "Actor.h"
//#include "Player.h"

class Script;
class MeshRenderer;
class Actor;

template<typename T>
static unique_ptr<T> CreateScriptComponent(shared_ptr<Actor> actor)
{
	unique_ptr<T> scriptComponent = make_unique<T>();

	actor->scriptComponents.push_back(scriptComponent);

	return scriptComponent;
//	return T + 1;
}

class Factory
{
public:
	Factory();
	~Factory();

//	template<typename T>
//	static void CreateScriptComponent(shared_ptr<Actor> actor)
//	{
//
//	}

//	static void CreateScriptComponent(shared_ptr<Actor> actor, unique_ptr<Script> script);

	static shared_ptr<Actor> CreateActor(string name, shared_ptr<MeshRenderer> meshRenderer);

	template<typename T>
	static shared_ptr<T> CreateActor(string name, shared_ptr<MeshRenderer> meshRenderer);
	
	
	//shared_ptr<T> CreateActor(string name, shared_ptr<MeshRenderer> meshRenderer);
};

