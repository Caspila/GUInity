#include "MeshCollider.hpp"
#include "Physics.hpp"
#include "Actor.hpp"
#include "Converter.hpp"

MeshCollider::MeshCollider()
{
#ifdef GUINITY_DEBUG
nCount++;
#endif
}


MeshCollider::~MeshCollider()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "MeshCollider destroyed (" << nCount << " remaining)" << endl;
#endif
}

void MeshCollider::init()
{

	shape = Physics::createMeshCollider(getActor());
    
}

void MeshCollider::tick(float deltaSeconds)
{
    PxConvexMeshGeometry geo;
    shape->getConvexMeshGeometry(geo);
    
    //PxMeshScale scale = geo.scale;
    geo.scale.scale = glmVec3ToPhysXVec3(getActor()->transform->scale);
    //geo.scale.rotation = glmQuatToPhysXQuat(getActor()->transform->rotationQuat);
    
    shape->setGeometry(geo);
    
}


