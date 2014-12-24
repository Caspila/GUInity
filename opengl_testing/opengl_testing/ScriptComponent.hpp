#pragma once
#include "Module.hpp"
#include "Script.hpp"
class Actor;
//class Script;

// template < class T >
class ScriptComponent
#ifdef GUINITY_DEBUG
	:public StaticCounter<ScriptComponent>
#endif
{
public:
	//template<class T>
	//ScriptComponent<T>(shared_ptr<Actor> actor);
	ScriptComponent();//weak_ptr<Actor> actor);//, shared_ptr<Script> script);


	virtual ~ScriptComponent();

	//shared_ptr<Script> script;
	//shared_ptr<Script> script;
	weak_ptr<Actor> actor;

	shared_ptr<Actor> getActor();
	void setActor(weak_ptr<Actor> actor);

	virtual void awake() {};
	virtual void tick(float deltaSecods) {};

private:
	//ScriptComponent();
};

