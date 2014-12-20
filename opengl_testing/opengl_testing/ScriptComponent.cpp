#include "ScriptComponent.h"

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
ScriptComponent::ScriptComponent(shared_ptr<Script> script, shared_ptr<Actor> actor)
{
	//this->script.reset(script.get());;
	this->script = script;
	this->actor = actor;

#ifdef GUINITY_DEBUG
	nCount++;
#endif
}


ScriptComponent::~ScriptComponent()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "ScriptComponent destroyed (" << nCount << " remaining)" << endl;
#endif
}
