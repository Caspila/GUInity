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
	static void notify(EventType type, shared_ptr<Component> component)
	{
		for (auto x : observers)
		{
			x->onNotify(type, component);
		}

	}

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