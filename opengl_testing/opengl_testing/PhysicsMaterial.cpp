#include "PhysicsMaterial.h"


PhysicsMaterial::PhysicsMaterial(float friction, float dynamicFriction, float restitution, shared_ptr<PxMaterial> material)
{
	this->friction = friction;
	this->dynamicFriction = dynamicFriction;
	this->restitution = restitution;

	this->material = material;
}



PhysicsMaterial::~PhysicsMaterial()
{
	cout << "PhysicsMaterial destroyed" << endl;
}
