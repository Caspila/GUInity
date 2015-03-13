#include "PhysicsMaterial.hpp"
#include <Physics.hpp>

//
//PhysicsMaterial::PhysicsMaterial(float friction, float dynamicFriction, float restitution, shared_ptr<PxMaterial> material)
//{
//	this->friction = friction;
//	this->dynamicFriction = dynamicFriction;
//	this->restitution = restitution;
//
//	this->material = material;
//
//#ifdef GUINITY_DEBUG
//	nCount++;
//#endif
//}

PhysicsMaterial::PhysicsMaterial(float friction, float dynamicFriction, float restitution) : material()
{
	this->friction = friction;
	this->dynamicFriction = dynamicFriction;
	this->restitution = restitution;
	
	this->material = Physics::createMaterial(friction, dynamicFriction, restitution);
	material->setRestitutionCombineMode(PxCombineMode::eAVERAGE);

#ifdef GUINITY_DEBUG
	nCount++;
#endif
}



PhysicsMaterial::~PhysicsMaterial()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "PhysicsMaterial destroyed (" << nCount << " remaining)" << endl;
#endif
}

PxMaterial*  PhysicsMaterial::getMaterial()
{
	return material;
}