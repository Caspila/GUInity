#include "CapsuleCollider.hpp"
#include "Physics.hpp"
#include "Math.hpp"
#include "Actor.hpp"

CapsuleCollider::CapsuleCollider(RotateAxis orientation, float halfHeight, float radius,PxVec3 center = PxVec3(0,0,0))
{
    initWithData = true;
    this->orientation = orientation;
    this->halfHeight = halfHeight;
    this->radius = radius;
    this->center = center;
    
    
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

CapsuleCollider::CapsuleCollider()
{
    initWithData = false;
    
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}


CapsuleCollider::~CapsuleCollider()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "CapsuleCollider destroyed (" << nCount << " remaining)" << endl;
#endif
}


void CapsuleCollider::init()
{
//    shape = !initWithData ?
//    Physics::createCapsuleCollider(getActor()):
//    Physics::createCapsuleCollider(radius,halfHeight,orientation,center,getActor());

    if(initWithData)
        shape = Physics::createCapsuleCollider(radius,halfHeight,orientation,center,getActor());
    else
    {
        shared_ptr<MeshFilter> meshFilter = getActor()->GetComponent<MeshFilter>();
    
        radius = 0.5f;
        halfHeight = 0.5f;
        orientation = RotateAxis::x;
        center = PxVec3(0, 0, 0);
        
        if(meshFilter)
            meshFilter->getCapsuleGeometry(getActor(), radius, halfHeight, orientation, center);
        
        shape = Physics::createCapsuleCollider(radius,halfHeight,orientation,center,getActor());
    }
}

void CapsuleCollider::setOrientation(RotateAxis orientation)
{
    Physics::setCapsuleOrientation(shape,orientation);
    
    this->orientation = orientation;

}

void CapsuleCollider::setHeight(float height)
{
	PxCapsuleGeometry geometry;
	shape->getCapsuleGeometry(geometry);

	geometry.halfHeight = height;

	shape->setGeometry(geometry);

}

void CapsuleCollider::setRadius(float radius)
{

	PxCapsuleGeometry geometry;
	shape->getCapsuleGeometry(geometry);

	geometry.radius = radius;

	shape->setGeometry(geometry);
}

shared_ptr<ComponentDescription> CapsuleCollider::getComponentDescription()
{
    
    PxCapsuleGeometry geo;
    shape->getCapsuleGeometry(geo);
    
    return make_shared<CapsuleColliderDescription>(geo.halfHeight, geo.radius,orientation);
}

void CapsuleCollider::deserialize(shared_ptr<ComponentDescription> desc)
{
    
    shared_ptr<CapsuleColliderDescription> capsuleColDesc = dynamic_pointer_cast<CapsuleColliderDescription>(desc);
    this->radius = capsuleColDesc->radius;
    this->halfHeight = capsuleColDesc->halfHeight;
    this->orientation = capsuleColDesc->orientation;
    this->center = capsuleColDesc->center;
    initWithData = true;
}