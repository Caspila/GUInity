#include "Component.hpp"

#ifdef GUINITY_DEBUG
int Component::count = 0;
#endif

/** Default Constructor*/
Component::Component()
{
#ifdef GUINITY_DEBUG
	count++;
#endif
}

/** Default Destructor. Virtual because is parent class*/
Component::~Component()
{
#ifdef GUINITY_DEBUG
	count--;
	cout << "-Component destroyed (" << count << " remaining)" << endl;
#endif
}

/** getter for Actor */
shared_ptr<Actor> Component::getActor()
{
	shared_ptr<Actor> actorLock = actor.lock();
	if (actorLock)
		return actorLock;

	// This should never happen because only the actor should have a handle to a component.
	// If the actor does not exist anymore, this component should be automatically released
	// because of smart pointer
	cerr << "ScriptComponent trying to get an actor that does not exist" << endl;

	return nullptr;
}

/** setter for Actor */
void Component::setActor(weak_ptr<Actor> actor)
{
	this->actor = actor;
}