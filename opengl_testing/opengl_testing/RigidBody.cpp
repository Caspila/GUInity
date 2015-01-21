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

	notify(NewRigidBody, shared_from_this(), getActor()->editorFlag);
}

void RigidBody::tick(float deltaSeconds)
{

	shared_ptr<Actor> actor = getActor();

    
//	physxRigidBody->setGlobalPose(transformToPhysXTransform(actor->transform));
    	physxRigidBody->setGlobalPose(PxTransform(glmMat4ToPhysxMat4(actor->transform->getModelMatrix())));
}

void RigidBody::setKinematic(bool isKinematic)
{
	physxRigidBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, isKinematic);
}

bool RigidBody::getKinematic()
{
    return physxRigidBody->getRigidBodyFlags() & (PxRigidBodyFlag::eKINEMATIC);
}

void RigidBody::setActive(bool isActive)
{
//    cout << "Disabled RigidBody" << endl;
    
    physxRigidBody->setActorFlag(PxActorFlag::eVISUALIZATION, isActive);
	physxRigidBody->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, !isActive);

    
}


shared_ptr<ComponentDescription> RigidBody::getComponentDescription()
{
    return make_shared<RigidBodyDescription>(getKinematic());
}

void RigidBody::deserialize(shared_ptr<ComponentDescription> desc)
{
    
}