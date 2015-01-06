#include "RigidStatic.hpp"
#include "Physics.hpp"
#include "Converter.hpp"
#include "Actor.hpp"

RigidStatic::RigidStatic()
{
}


RigidStatic::~RigidStatic()
{
}

void RigidStatic::init()
{
	physxRigidStatic = Physics::createRigidDynamic(getActor());
	//physxRigidStatic->setActorFlag(PxActorFlag::eDISABLE_SIMULATION,true);
	physxRigidStatic->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC, true);

	notify(NewRigidStatic, shared_from_this(), getActor()->editorFlag);
}

void RigidStatic::tick(float deltaSeconds)
{
	shared_ptr<Actor> actor = getActor();

	physxRigidStatic->setGlobalPose(transformToPhysXTransform(actor->transform));
}

shared_ptr<ComponentDescription> RigidStatic::getComponentDescription()
{
    return make_shared<RigidStaticDescription>();
}

void RigidStatic::deserialize(shared_ptr<ComponentDescription> desc)
{
    
}