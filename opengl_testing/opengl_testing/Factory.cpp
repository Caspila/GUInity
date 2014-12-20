#include "Factory.h"


Factory::Factory()
{
}


Factory::~Factory()
{
}

void Factory::CreateScriptComponent(shared_ptr<Actor> actor, shared_ptr<Script> script)
{
	ScriptComponent scriptComponent(script, actor);
	actor->scriptComponents.push_back(scriptComponent);
}

shared_ptr<Actor> Factory::CreateActor(string name, shared_ptr<MeshRenderer> meshRenderer)
{
	shared_ptr<Actor> actor = make_shared<Actor>(name, meshRenderer);
	actor->transform->setActor(actor);

	return actor;
}

template<class T>
shared_ptr<T> Factory::CreateActor(string name, shared_ptr<MeshRenderer> meshRenderer)
{
	shared_ptr<T> actor = make_shared<T>(name, meshRenderer);
	actor->transform->setActor(actor);

	return actor;
}

template shared_ptr<Actor> Factory::CreateActor<Actor>(string name, shared_ptr<MeshRenderer> meshRenderer);
template shared_ptr<Player> Factory::CreateActor<Player>(string name, shared_ptr<MeshRenderer> meshRenderer);
