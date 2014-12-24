#include "Factory.hpp"
#include "Actor.hpp"
#include "Transform.hpp"
#include "Script.hpp"
#include "ScriptComponent.hpp"

Factory::Factory()
{
}


Factory::~Factory()
{
}

//template<class T>
//static void CreateScriptComponent(shared_ptr<Actor> actor);
//template<typename T>
//void Factory::CreateScriptComponent(shared_ptr<Actor> actor)
//{
//	//unique_ptr<T> uniqueScript = make_unique<T>();
//	//ScriptComponent scriptComponent(uniqueScript, actor);
//	//actor->scriptComponents.push_back(scriptComponent);
//}

//void Factory::CreateScriptComponent(shared_ptr<Actor> actor, unique_ptr<Script> script)
//{
//	ScriptComponent scriptComponent(script, actor);
//	actor->scriptComponents.push_back(scriptComponent);
//}

shared_ptr<Actor> Factory::CreateActor(string name, shared_ptr<MeshRenderer> meshRenderer)
{
	shared_ptr<Actor> actor = make_shared<Actor>(name, meshRenderer);
	actor->transform->setActor(actor);

	return actor;
}

template<typename T>
shared_ptr<T> Factory::CreateActor(string name, shared_ptr<MeshRenderer> meshRenderer)
{
	shared_ptr<T> actor = make_shared<T>(name, meshRenderer);
	actor->transform->setActor(actor);

	return actor;
}

template shared_ptr<Actor> Factory::CreateActor<Actor>(string name, shared_ptr<MeshRenderer> meshRenderer);

//template void Factory::CreateScriptComponent<Script>(shared_ptr<Actor> actor);
