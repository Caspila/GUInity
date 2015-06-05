#include "RigidStatic.hpp"
#include "Physics.hpp"
#include "Converter.hpp"
#include "Actor.hpp"
#include "Transform.hpp"

RigidStatic::RigidStatic()
{
    physxRigidStatic = nullptr;
}


RigidStatic::~RigidStatic()
{
}

void RigidStatic::init()
{
	physxRigidStatic = Physics::createRigidDynamic(getActor());
	//physxRigidStatic->setActorFlag(PxActorFlag::eDISABLE_SIMULATION,true);
	physxRigidStatic->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC, true);

	notify(NewRigidStatic, shared_from_this(), getActor()->getEditorFlag());
}

void RigidStatic::tick(float deltaSeconds)
{
	shared_ptr<Actor> actor = getActor();

//	physxRigidStatic->setGlobalPose(transformToPhysXTransform(actor->transform));
   	physxRigidStatic->setGlobalPose(PxTransform(glmMat4ToPhysxMat4(actor->transform->getPosRotMatrix())));
}

shared_ptr<ComponentDescription> RigidStatic::getComponentDescription()
{
    return make_shared<RigidStaticDescription>();
}

void RigidStatic::deserialize(shared_ptr<ComponentDescription> desc)
{
    
}

void RigidStatic::setActive(bool isActive)
{
     physxRigidStatic->setActorFlag(PxActorFlag::eVISUALIZATION, isActive);
	physxRigidStatic->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, !isActive);
   
    
//        cout << "Disabled RigidStatic" << isActive<< endl;
    
}

PxRigidDynamic* RigidStatic::getRigidDynamic()
{
    return physxRigidStatic;
}
