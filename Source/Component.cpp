#include "Component.hpp"

#ifdef GUINITY_DEBUG
int Component::count = 0;
#endif

/** Default Constructor*/
Component::Component()
: isActive{true}
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

/** Used when been deserialized or cloned
 @param [in] initWithData true if this component data will come from clone of deserialization, false if it's a new component being creates
 */
void Component::setCopyMode(bool initWithData)
{
    this->initWithData = initWithData;
}

/** Getter for owner Actor
 @return shared_ptr for the owner */
shared_ptr<Actor> Component::getActor()
{
	shared_ptr<Actor> actorLock = actor.lock();
	if (actorLock)
		return actorLock;
    
	// This should never happen because only the actor should have a handle to a component.
	// If the actor does not exist anymore, this component should be automatically released
	// because of smart pointer
	cerr << "Component trying to get an actor that does not exist" << endl;
    
	return nullptr;
}

/** Setter for owner Actor
 @param owner Actor*/
void Component::setActor(weak_ptr<Actor> actor)
{
	this->actor = actor;
}


/** isActive Getter
 @return true if Component is Active, false otherwise */
bool Component::getIsActive()
{
    return  isActive;
}
/** isActive Setter
 @param[in] true if Component should be Active, false otherwise */
void Component::setIsActive(bool isActive)
{
    this->isActive = isActive;
}


