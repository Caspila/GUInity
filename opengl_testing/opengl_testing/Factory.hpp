#pragma once

#include "Module.hpp"
#include "Actor.hpp"
#include "Subject.hpp"
//#include "Player.h"

class Script;
class MeshRenderer;

class Factory : public Subject<Factory>
{
public:
	Factory();
	~Factory();

	static shared_ptr<Actor> CreateActor(string name);
	static shared_ptr<Actor> CreateEditorActor(string name);
};

