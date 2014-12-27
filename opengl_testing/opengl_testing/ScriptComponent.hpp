#pragma once
#include "Module.hpp"
//#include "Script.hpp"
#include "Component.hpp"
class Actor;
//class Script;

// template < class T >
class ScriptComponent: public Component
#ifdef GUINITY_DEBUG
	, public StaticCounter<ScriptComponent>
#endif
{
public:
	//template<class T>
	//ScriptComponent<T>(shared_ptr<Actor> actor);
	ScriptComponent();//weak_ptr<Actor> actor);//, shared_ptr<Script> script);


	virtual ~ScriptComponent();

	//shared_ptr<Script> script;
	//shared_ptr<Script> script;

	virtual void init() {};
	virtual void awake() override {} ;
	virtual void tick(float deltaSecods) override {};



	virtual void onCollision(Actor* actor) {};
	virtual void onTrigger(Actor* actor) {};

private:
	//ScriptComponent();
};

