#include "MeshCollider.hpp"
#include "Physics.hpp"


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


