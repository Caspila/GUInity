#include "ScriptComponent.hpp"

//template<class T>
//ScriptComponent::ScriptComponent<T>(shared_ptr<Actor> actor)
//{
//	this->script = make_unique<T>();
//	//this->script.reset(script.get());;
//	this->actor = actor;
//
//#ifdef GUINITY_DEBUG
//	nCount++;
//#endif
//}

ScriptComponent::ScriptComponent()//weak_ptr<Actor> actor)//, shared_ptr<Script> script)
{
	//this->script.reset(script.get());;
	//this->script = make_unique<Script>(script);
	//this->script = script;
	//this->actor = actor;

#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

ScriptComponent::~ScriptComponent()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << " <- Base ScriptComponent destroyed (" << nCount << " remaining)" << endl;
#endif
}

