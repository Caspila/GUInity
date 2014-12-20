#include "Script.h"


Script::Script()
{
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}


Script::~Script()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "<-- Base Script Destroyed (" << nCount << " remaining)" << endl;
#endif
	
}

void Script::tick(weak_ptr<Actor> actor, float deltaSeconds)
{
	shared_ptr<Actor> actorLock = actor.lock();
	if (actorLock)
	{
		currentActor = actorLock;
		//currentActor = actor;
		tick(deltaSeconds);
		currentActor = nullptr;
}
}

shared_ptr<Actor> Script::getActor()
{
	return currentActor;
	//shared_ptr<Actor> actorLock = currentActor.lock();
	//if (actorLock)
	//	return actorLock;
	//
	//return nullptr;
}