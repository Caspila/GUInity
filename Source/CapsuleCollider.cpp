#include "CapsuleCollider.hpp"
#include "Physics.hpp"
#include "Math.hpp"
#include "Actor.hpp"
#include "MeshFilter.hpp"
/** Deserialization Constructor*/
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
/** Default Constructor*/
CapsuleCollider::CapsuleCollider()
{
    initWithData = false;
    
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

/** Default Destructor*/
CapsuleCollider::~CapsuleCollider()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "CapsuleCollider destroyed (" << nCount << " remaining)" << endl;
#endif
}



/** orientation Setter*/
void CapsuleCollider::setOrientation(RotateAxis orientation)
{
	Physics::setCapsuleOrientation(shape, orientation);

	this->orientation = orientation;
}
/** orientation Getter*/
RotateAxis CapsuleCollider::getOrientation()
{
	return orientation;
}

/** height Setter*/
void CapsuleCollider::setHeight(float height)
{
	PxCapsuleGeometry geometry;
	shape->getCapsuleGeometry(geometry);

	geometry.halfHeight = height;

	shape->setGeometry(geometry);

}
/** height Getter*/
float CapsuleCollider::getHeight()
{
	return halfHeight;
}

/** radius Setter*/
void CapsuleCollider::setRadius(float radius)
{

	PxCapsuleGeometry geometry;
	shape->getCapsuleGeometry(geometry);

	geometry.radius = radius;

	shape->setGeometry(geometry);
}
/** radius Getter*/
float CapsuleCollider::getRadius()
{
	return radius;
}

/** Init component override. Create a new Capsule Shape in the PhysX scene. */
void CapsuleCollider::init()
{

	// Deserialize
    if(initWithData)
        shape = Physics::createCapsuleCollider(radius,halfHeight,orientation,center,getActor());
    // Create new one
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

	// Sets the material as the default one
	Collider::init();
}

/** Get a description for the current component*/
shared_ptr<ComponentDescription> CapsuleCollider::getComponentDescription()
{
    
    PxCapsuleGeometry geo;
    shape->getCapsuleGeometry(geo);
    
    return make_shared<CapsuleColliderDescription>(geo.halfHeight, geo.radius,orientation);
}

/** Deserialize a component description into this collider */
void CapsuleCollider::deserialize(shared_ptr<ComponentDescription> desc)
{
    shared_ptr<CapsuleColliderDescription> capsuleColDesc = dynamic_pointer_cast<CapsuleColliderDescription>(desc);
    this->radius = capsuleColDesc->radius;
    this->halfHeight = capsuleColDesc->halfHeight;
    this->orientation = capsuleColDesc->orientation;
    this->center = capsuleColDesc->center;
    initWithData = true;
}