#include "SphereCollider.hpp"
#include "Physics.hpp"
#include "Actor.hpp"
#include "Converter.hpp"
#include "MeshFilter.hpp"
#include "PhysicsMaterial.hpp"
#include "AssetDatabase.hpp"

/** Deserialization Constructor*/
SphereCollider::SphereCollider(float radius, PxVec3 center = PxVec3(0,0,0))
{
    this->radius = radius;
    this->center = center;
    
    setCopyMode(true);
    
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

/** Default Constructor*/
SphereCollider::SphereCollider()
{
    
    setCopyMode(false);
    
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

/** Default Destructor*/
SphereCollider::~SphereCollider()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "SphereCollider destroyed (" << nCount << " remaining)" << endl;
#endif
}

/** radius Getter
 @return radius of the sphere */
float SphereCollider::getRadius() const
{
	return radius;
}

/** radius Setter
 @param [in] newRadius the radius of the sphere */
void SphereCollider::setRadius(float newRadius)
{
	this->radius = newRadius;
    
    if(shape)
    {
	// Update PhysX scene
	PxSphereGeometry sphereGeometry;
    
	shape->getSphereGeometry(sphereGeometry);
    
	sphereGeometry.radius = newRadius;
    
	shape->setGeometry(sphereGeometry);
    }
    
}

/** Init component override. Create a new Sphere Shape in the PhysX scene. */
void SphereCollider::init()
{
	// Deserializing
    if(initWithData)
    {
        shape = Physics::createSphereCollider(radius,center,getActor());
        
        // The physics material is set but it's not yet linked to the shape
        if(physicsMaterial!=nullptr)
            setPhysicsMaterial(getPhysicsMaterial());
        
        setRadius(radius);
        
        setIsTrigger(isTrigger);
        setQueryOnly(isQueryOnly);
        
    }
    // Create a new one
	else
    {
        shared_ptr<MeshFilter> meshFilter = getActor()->GetComponent<MeshFilter>();
        
        radius = 0.5f;
        center = PxVec3(0,0,0);
        
        if(meshFilter)
            meshFilter->getSphereSize(getActor(), radius, center);
        
        shape = Physics::createSphereCollider(radius,center,getActor());
        // Sets the material as the default one
        Collider::init();
        
    }
    
}

/** Clones current component (Prototype Design Pattern)
 @return shared_ptr to cloned SphereCollider Component
 */
shared_ptr<Component> SphereCollider::clone() {
    shared_ptr<SphereCollider> compClone = make_shared<SphereCollider>(radius,center);
    
    compClone->isTrigger = isTrigger;
    compClone->isQueryOnly = isQueryOnly;
    
    
    if(physicsMaterial!=nullptr)
        compClone->setPhysicsMaterial(getPhysicsMaterial());

    return compClone;
};

/** Get a description for the current component*/
shared_ptr<ComponentDescription> SphereCollider::getComponentDescription()
{
    PxSphereGeometry geo;
    shape->getSphereGeometry(geo);
    
    return make_shared<SphereColliderDescription>(center,isTrigger,isQueryOnly,getPhysicsMaterial()->getAssetID(),geo.radius);
}

/** Deserialize a component description into this collider */
void SphereCollider::deserialize(shared_ptr<ComponentDescription> desc)
{
    shared_ptr<SphereColliderDescription> sphereColDesc = dynamic_pointer_cast<SphereColliderDescription>(desc);
    this->radius = sphereColDesc->radius;

    this->center = sphereColDesc->center;
    this->isQueryOnly = sphereColDesc->isQueryOnly;
    this->isTrigger = sphereColDesc->isTrigger;
    
    setPhysicsMaterial(AssetDatabase::getAsset<PhysicsMaterial>(sphereColDesc->physicsMaterialID));
    
    setCopyMode(true);
}

/** Looks for a MeshComponent and gets the extent for the collider */
void SphereCollider::recalculateBounds()
{
    shared_ptr<MeshFilter> meshFilter = getActor()->GetComponent<MeshFilter>();
    
    float radius = 0.5f;
    PxVec3   center(0,0,0);
    
    if(meshFilter)
        meshFilter->getSphereSize(getActor(), radius, center);
    
    setRadius(radius);
    
}

