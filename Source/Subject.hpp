#pragma once

#include "Module.hpp"
#include <vector>
#include "Observer.hpp"
#include "Enums.hpp"

class Component;

using namespace std;


/** Subject class for the Observer pattern
 https://en.wikipedia.org/wiki/Observer_pattern
 */
template <typename T>
class Subject
{
    
private:
    /** List of observers of this class */
	static vector<shared_ptr<Observer>> observers;
    
protected:
    /** Notifies all observers
     @param[in] type The type of the notification
     @param[in] component The Component that triggered the notification
     @param[in] isEditor If the notification belongs to the Editor realm
     */
	static void notify(ComponentEventType type, shared_ptr<Component> component, bool isEditor)
	{
		for (auto& x : observers)
		{
			x->onNotify(type, component, isEditor);
		}
        
	}
    /** Notifies all observers
     @param[in] type The type of the notification
     @param[in] actor The Actor that triggered the notification
     @param[in] isEditor If the notification belongs to the Editor realm
     */
	static void notify(ActorEventType type, shared_ptr<Actor> actor, bool isEditor)
	{
		for (auto& x : observers)
		{
			x->onNotify(type, actor, isEditor);
		}
        
	}
    
    
public:
    
    /** Add observer to the observers list
     @param[in] observer Observer to be added
     */
	static void addObserver(shared_ptr<Observer> observer)
	{
		observers.push_back(observer);
	}
    /** Remove observer from the observers list
     @param[in] observer Observer to be removed
     */
	static void removeObserver(shared_ptr<Observer> observer)
	{
		auto it = find(observers.begin(), observers.end(), observer);
        
		if (it != observers.end())
		{
			observers.erase(it);
		}
	}
};

template <typename T> vector<shared_ptr<Observer>> Subject<T>::observers;