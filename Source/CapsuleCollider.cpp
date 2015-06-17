#include "CapsuleCollider.hpp"
#include "Physics.hpp"
#include "Math.hpp"
#include "Actor.hpp"
#include "MeshFilter.hpp"
#include "PhysicsMaterial.hpp"
#include "AssetDatabase.hpp"

/** Deserialization Constructor*/
CapsuleCollider::CapsuleCollider(RotateAxis orientation, float halfHeight, float radius,PxVec3 center = PxVec3(0,0,0))
{
    setCopyMode(true);
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
    setCopyMode(false);
    
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
    if(shape)
        Physics::setCapsuleOrientation(shape, orientation);

	this->orientation = orientation;
}
/** orientation Getter*/
RotateAxis CapsuleCollider::getOrientation() const
{
	return orientation;
}

/** height Setter*/
void CapsuleCollider::setHeight(float height)
{
    this->halfHeight = halfHeight;
    if(shape)
    {
	PxCapsuleGeometry geometry;
	shape->getCapsuleGeometry(geometry);

	geometry.halfHeight = height;

	shape->setGeometry(geometry);
    }

}
/** height Getter*/
float CapsuleCollider::getHeight() const
{
	return halfHeight;
}

/** radius Setter*/
void CapsuleCollider::setRadius(float radius)
{
    this->radius = radius;
    if(shape)
    {
	PxCapsuleGeometry geometry;
	shape->getCapsuleGeometry(geometry);

	geometry.radius = radius;

	shape->setGeometry(geometry);
    }
}
/** radius Getter*/
float CapsuleCollider::getRadius() const
{
	return radius;
}

/** Init component override. Create a new Capsule Shape in the PhysX scene. */
void CapsuleCollider::init()
{

	// Deserialize
    if(initWithData)
    {
        shape = Physics::createCapsuleCollider(radius,halfHeight,orientation,center,getActor());
        
        // The physics material is set but it's not yet linked to the shape
        if(physicsMaterial!=nullptr)
            setPhysicsMaterial(getPhysicsMaterial());
        
        setOrientation(orientation);
        setRadius(radius);
        setHeight(halfHeight);
        
        setIsTrigger(isTrigger);
        setQueryOnly(isQueryOnly);
        
    }
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
        
        // Sets the material as the default one
        Collider::init();
    }


}


/** Looks for a MeshComponent and gets the extent for the collider */
void CapsuleCollider::recalculateBounds()
{
    shared_ptr<MeshFilter> meshFilter = getActor()->GetComponent<MeshFilter>();
    
    PxVec3   center(0,0,0);
    float radius = 0.5f;
    float halfHeight = 0.5f;
    RotateAxis orientation = RotateAxis::x;

    
    if(meshFilter)
        meshFilter->getSphereSize(getActor(), radius, center);
    
    setRadius(radius);
    setHeight(halfHeight);
    setOrientation(orientation);
    
}

/** Clones current component (Prototype Design Pattern)
 @return shared_ptr to cloned CapsuleCollider Component
 */
shared_ptr<Component> CapsuleCollider::clone() {
    shared_ptr<CapsuleCollider> compClone = make_shared<CapsuleCollider>(orientation, halfHeight, radius, center);
    
    compClone->isTrigger = isTrigger;
    compClone->isQueryOnly = isQueryOnly;
    
    
    if(physicsMaterial!=nullptr)
        compClone->setPhysicsMaterial(getPhysicsMaterial());
    return compClone;
};

/** Get a description for the current component*/
shared_ptr<ComponentDescription> CapsuleCollider::getComponentDescription()
{
    
    PxCapsuleGeometry geo;
    shape->getCapsuleGeometry(geo);
    
    return make_shared<CapsuleColliderDescription>(center,isTrigger,isQueryOnly,getPhysicsMaterial()->getAssetID(),geo.halfHeight, geo.radius,orientation);
}

/** Deserialize a component description into this collider */
void CapsuleCollider::deserialize(shared_ptr<ComponentDescription> desc)
{
    shared_ptr<CapsuleColliderDescription> capsuleColDesc = dynamic_pointer_cast<CapsuleColliderDescription>(desc);
    this->radius = capsuleColDesc->radius;
    this->halfHeight = capsuleColDesc->halfHeight;
    this->orientation = capsuleColDesc->orientation;

    this->center = capsuleColDesc->center;
    this->isQueryOnly = capsuleColDesc->isQueryOnly;
    this->isTrigger = capsuleColDesc->isTrigger;
    
        setPhysicsMaterial(AssetDatabase::getAsset<PhysicsMaterial>(capsuleColDesc->physicsMaterialID));
    
    setCopyMode(true);
}