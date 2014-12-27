#include "Component.hpp"

#ifdef GUINITY_DEBUG
int Component::count = 0;
#endif

Component::Component()
{
#ifdef GUINITY_DEBUG
	count++;
#endif
}


Component::~Component()
{
#ifdef GUINITY_DEBUG
	count--;
	cout << "-Component destroyed (" << count << " remaining)" << endl;
#endif
}

shared_ptr<Actor> Component::getActor()
{
	shared_ptr<Actor> actorLock = actor.lock();
	if (actorLock)
		return actorLock;

	cerr << "ScriptComponent trying to get an actor that does not exist" << endl;

	return nullptr;
}

void Component::setActor(weak_ptr<Actor> actor)
{
	this->actor = actor;
}