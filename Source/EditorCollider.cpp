#include "EditorCollider.hpp"
#include "Actor.hpp"
#include "Physics.hpp"
#include "Transform.hpp"



/** gameActor setter*/
void EditorCollider::setGameActor(shared_ptr<Actor> gameActor)
{
	this->gameActor = gameActor;
}

/** gameActor getter*/
shared_ptr<Actor> EditorCollider::getGameActor()
{
	return gameActor.lock();
}

/** Component tick override. Updates the fake collider position and rotation to match the real Game Actor */
void EditorCollider::init()
{
	physxRigidStatic = Physics::createRigidDynamic(getActor());
	physxRigidStatic->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC, true);

	notify(NewEditorCollider, shared_from_this(), getActor()->getEditorFlag());
}

/** Component init override. Initializes the rigid body in the PhysX scene. */
void EditorCollider::tick(float deltaSeconds)
{
	shared_ptr<Actor> gameActorLock = gameActor.lock();

	shared_ptr<Actor> myActor = getActor();

	myActor->transform->position = gameActorLock->transform->position;
	myActor->transform->rotationQuat = gameActorLock->transform->rotationQuat;
}

/** physxRigidStatic getter*/
PxRigidDynamic* EditorCollider::getRigidStatic()
{
	return physxRigidStatic;
}

