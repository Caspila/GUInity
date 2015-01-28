#include "EditorCollider.hpp"
#include "Actor.hpp"
#include "Physics.hpp"


EditorCollider::EditorCollider()
{
}


EditorCollider::~EditorCollider()
{
}


void EditorCollider::init()
{
	physxRigidStatic = Physics::createRigidDynamic(getActor());
	physxRigidStatic->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC, true);

	notify(NewEditorCollider, shared_from_this(), getActor()->editorFlag);
}

void EditorCollider::tick(float deltaSeconds)
{
	shared_ptr<Actor> gameActorLock = gameActor.lock();

	shared_ptr<Actor> myActor = getActor();

	myActor->transform->position = gameActorLock->transform->position;
	myActor->transform->rotationQuat = gameActorLock->transform->rotationQuat;
	//gameActorLock->transform->position = myActor->transform->position;
	//gameActorLock->transform->rotationQuat = myActor->transform->rotationQuat;

}


void EditorCollider::setGameActor(shared_ptr<Actor> gameActor)
{
	this->gameActor = gameActor;
}