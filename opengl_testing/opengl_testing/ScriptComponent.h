#pragma once
#include "Module.h"
//#include "Script.h"
class Script;
class Actor;
class ScriptComponent
{
public:
	ScriptComponent(shared_ptr<Script> script,	shared_ptr<Actor> actor);
	virtual ~ScriptComponent();

	shared_ptr<Script> script;
	shared_ptr<Actor> actor;

	virtual void tick(float deltaSecods) {};
};

