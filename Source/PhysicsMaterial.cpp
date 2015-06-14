#include "PhysicsMaterial.hpp"
#include <Physics.hpp>

/** Constructor
 @param[in] friction The friction of the material
 @param[in] dynamicFriction The dynamic friction of the material
 @param[in] restitution The restiturion of the material
 */
PhysicsMaterial::PhysicsMaterial(float friction, float dynamicFriction, float restitution)
: friction{friction}, dynamicFriction{dynamicFriction}, restitution{restitution}
{
	this->material = Physics::createMaterial(friction, dynamicFriction, restitution);
	material->setRestitutionCombineMode(PxCombineMode::eAVERAGE);

#ifdef GUINITY_DEBUG
	nCount++;
#endif
}


    /** Default Destructor */
PhysicsMaterial::~PhysicsMaterial()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "PhysicsMaterial destroyed (" << nCount << " remaining)" << endl;
#endif
}

/** material Getter
 @return reference to the PhysX material
 */
PxMaterial *const  PhysicsMaterial::getMaterial() const
{
	return material;
}