#include "Script.h"


Script::Script()
{
}


Script::~Script()
{
	cout << "<-- Base Script Destroyed" << endl;
}

void Script::tick(shared_ptr<Actor> a, float deltaSeconds)
{
	currentActor = a;
	tick(deltaSeconds);
}

shared_ptr<Actor> Script::getActor()
{
	return currentActor;
}