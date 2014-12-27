#include "RigidBody.hpp"
#include "Physics.hpp"
#include "Converter.hpp"
#include "Actor.hpp"

RigidBody::RigidBody()
{
#ifdef GUINITY_DEBUG
nCount++;
#endif
}


RigidBody::~RigidBody()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "RigidBody destroyed (" << nCount << " remaining)" << endl;
#endif
}

void RigidBody::init()
{
	
	physxRigidBody = Physics::createRigidDynamic(getActor());

}

void RigidBody::tick(float deltaSeconds)
{

	shared_ptr<Actor> actor = getActor();

	physxRigidBody->setGlobalPose(transformToPhysXTransform(actor->transform));
}

void RigidBody::setKinematic(bool isKinematic)
{
	physxRigidBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, isKinematic);
}

void RigidBody::setActive(bool isActive)
{
	physxRigidBody->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, !isActive);
}