#include "BoxCollider.hpp"
#include "Physics.hpp"
#include "Actor.hpp"
#include "Converter.hpp"

using namespace physx;

BoxCollider::BoxCollider()
{
    initWithData = false;
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}


BoxCollider::BoxCollider(PxVec3 halfExtent, PxVec3 center)
{
    this->halfExtent = halfExtent;
    this->center = center;
    initWithData = true;
    
    
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

BoxCollider::~BoxCollider()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "BoxCollider destroyed (" << nCount << " remaining)" << endl;
#endif
}

void BoxCollider::init()
{
    if(initWithData)
        shape = Physics::createBoxCollider(halfExtent,center,getActor());
    else
    {
        shared_ptr<MeshFilter> meshFilter = getActor()->GetComponent<MeshFilter>();
        
        center = PxVec3(0, 0, 0);
        halfExtent= PxVec3(0.5f, 0.5f, 0.5f);
        
        if(meshFilter)
            meshFilter->getBoxSize(getActor(), halfExtent,center);
        
        shape = Physics::createBoxCollider(halfExtent,center,getActor());
    }
    
	//shape = halfExtent == glm::vec3(0,0,0) ? Physics::createBoxCollider(getActor()) : ;
}


shared_ptr<ComponentDescription> BoxCollider::getComponentDescription()
{
    return make_shared<BoxColliderDescription>(halfExtent);
}

void BoxCollider::deserialize(shared_ptr<ComponentDescription> desc)
{
    
    shared_ptr<BoxColliderDescription> boxColDesc = dynamic_pointer_cast<BoxColliderDescription>(desc);
    this->halfExtent = boxColDesc->halfExtent;
    this->center = boxColDesc->center;
    initWithData = true;
}