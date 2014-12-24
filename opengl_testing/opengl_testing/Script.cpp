#include "Script.hpp"


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

void Script::setActor(shared_ptr<Actor> actor)
{
	this->actor = actor;
}

//void Script::tick(float deltaSeconds)
//{
//	//shared_ptr<Actor> actorLock = actor.lock();
//	//if (actorLock)
//	//{
//	//	actor = actorLock;
//	//	//currentActor = actor;
//	//	tick(deltaSeconds);
//	//	currentActor = nullptr;
//	//}
//	tick(deltaSeconds);
//}


//void Script::tick(weak_ptr<Actor> actor, float deltaSeconds)
//{
//	shared_ptr<Actor> actorLock = actor.lock();
//	if (actorLock)
//	{
//		actor = actorLock;
//		//currentActor = actor;
//		tick(deltaSeconds);
//		currentActor = nullptr;
//	}
//}

shared_ptr<Actor> Script::getActor()
{
	return actor;
	//return currentActor;
	//shared_ptr<Actor> actorLock = currentActor.lock();
	//if (actorLock)
	//	return actorLock;
	//
	//return nullptr;
}