#pragma once

#include "Module.h"
#include "Actor.h"
#include "Player.h"

class Factory
{
public:
	Factory();
	~Factory();


	static void CreateScriptComponent(shared_ptr<Actor> actor, shared_ptr<Script> script);


	static shared_ptr<Actor> CreateActor(string name, shared_ptr<MeshRenderer> meshRenderer);

	template<class T>
	static shared_ptr<T> CreateActor(string name, shared_ptr<MeshRenderer> meshRenderer);
	
	
	//shared_ptr<T> CreateActor(string name, shared_ptr<MeshRenderer> meshRenderer);
};

