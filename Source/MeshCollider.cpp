#include "MeshCollider.hpp"
#include "Physics.hpp"
#include "Actor.hpp"
#include "Converter.hpp"
#include "Transform.hpp"
#include "PhysicsMaterial.hpp"

/** Default Constructor*/
MeshCollider::MeshCollider()
{
    setCopyMode(false);
    
#ifdef GUINITY_DEBUG
nCount++;
#endif
}

/** Default Destructor. Virtual because inherits from Collider*/
MeshCollider::~MeshCollider()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "MeshCollider destroyed (" << nCount << " remaining)" << endl;
#endif
}

/** Init component override. Create a new Mesh Shape in the PhysX scene. */
void MeshCollider::init()
{
	shape = Physics::createMeshCollider(getActor());

    if(initWithData)
    {
        PxMaterial* mat = physicsMaterial->getMaterial();
        PxMaterial* const newMat = const_cast<PxMaterial* const>(mat);
        
        shape->setMaterials(&newMat,1);
    }
    else
    {
        // Sets the material as the default one
        Collider::init();
    }
}

/** Component tick override. Updates the scale of the Mesh Shape in the PhysX scene. */
void MeshCollider::tick(float deltaSeconds)
{
    PxConvexMeshGeometry geo;
    shape->getConvexMeshGeometry(geo);
    
    //PxMeshScale scale = geo.scale;
    geo.scale.scale = glmVec3ToPhysXVec3(getActor()->transform->scale);
    //geo.scale.rotation = glmQuatToPhysXQuat(getActor()->transform->rotationQuat);
    
    shape->setGeometry(geo);
    
}

shared_ptr<Component> MeshCollider::clone()
{
    shared_ptr<MeshCollider> compClone = make_shared<MeshCollider>();
    
    compClone->setPhysicsMaterial(getPhysicsMaterial());
    compClone->setCopyMode(true);
    
    return compClone;
};


/** Get a description for the current component*/
shared_ptr<ComponentDescription> MeshCollider::getComponentDescription()
{
	return nullptr;
}
/** Deserialize a component description into this collider */
void MeshCollider::deserialize(shared_ptr<ComponentDescription> desc)
{

}

