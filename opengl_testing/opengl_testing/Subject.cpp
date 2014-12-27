#include "Subject.hpp"
#include "Component.hpp"
#include "Observer.hpp"


//template <typename T> vector<shared_ptr<Observer>> Subject<T>::observers;

//template <typename T>
//Subject<T>::Subject()
//{
//}
//
//
//template <typename T>
//Subject<T>::~Subject()
//{
//}

//template <typename T>
//void Subject<T>::removeObserver(shared_ptr<Observer> observer)
//{
//	auto it = find(observers.begin(), observers.end(), observer);
//
//	if (it != observers.end())
//	{
//		observers.erase(it);
//	}
//}

//template <typename T>
//void Subject<T>::notify(EventType type, shared_ptr<Component> component)
//{
//	for (auto x : observers)
//	{
//		x->onNotify(type, component);
//	}
//	
//}