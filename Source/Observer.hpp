#pragma once

//#include "Subject.h"
#include "Enums.hpp"
#include "Module.hpp"

class Component;
class Actor;

/** Observer class for the Observer pattern
 https://en.wikipedia.org/wiki/Observer_pattern
 */
class Observer
{
public:
    
    /** Receives notification
     @param[in] type The type of the notification
     @param[in] component The Component that triggered the notification
     @param[in] isEditor If the notification belongs to the Editor realm
     */
	virtual void onNotify(ComponentEventType type, shared_ptr<Component> component, bool isEditor) = 0;
    
    /** Receives notification
     @param[in] type The type of the notification
     @param[in] actor The Actor that triggered the notification
     @param[in] isEditor If the notification belongs to the Editor realm
     */
    virtual void onNotify(ActorEventType type, shared_ptr<Actor> actor, bool isEditor) = 0;
    
};

