#pragma once
#include "Module.h"
//#include "Script.h"
class Actor;
class Script;

class ScriptComponent
#ifdef GUINITY_DEBUG
	:public StaticCounter<ScriptComponent>
#endif
{
public:
	//template<class T>
	//ScriptComponent<T>(shared_ptr<Actor> actor);
	ScriptComponent(shared_ptr<Script> script, shared_ptr<Actor> actor);

	virtual ~ScriptComponent();

	shared_ptr<Script> script;
	weak_ptr<Actor> actor;

	virtual void tick(float deltaSecods) {};
};

