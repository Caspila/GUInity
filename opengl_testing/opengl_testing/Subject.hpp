#pragma once

#include "Module.hpp"
#include <vector>
#include "Observer.hpp"
#include "Enums.hpp"

class Component;

using namespace std;


template <typename T>
class Subject
{

private:
	static vector<shared_ptr<Observer>> observers;

protected:
	static void notify(ComponentEventType type, shared_ptr<Component> component, bool isEditor)
	{
		for (auto& x : observers)
		{
			x->onNotify(type, component, isEditor);
		}

	}
	static void notify(ActorEventType type, shared_ptr<Actor> actor, bool isEditor)
	{
		for (auto& x : observers)
		{
			x->onNotify(type, actor, isEditor);
		}

	}
	//static void notify(EventType type, shared_ptr<Component> component)
	//{
	//	for (auto x : observers)
	//	{
	//		x->onNotify(type, component);
	//	}
	//
	//}

	//static void notify(EventType type, shared_ptr<Actor> actor)
	//{
	//	for (auto x : observers)
	//	{
	//		x->onNotify(type, actor);
	//	}
	//
	//}


public:

	//Subject();
	//virtual ~Subject();

	static void addObserver(shared_ptr<Observer> observer)
	//void Subject<T>::addObserver(shared_ptr<Observer> observer)
	{
		observers.push_back(observer);
	}
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