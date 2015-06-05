#include "SphereCollider.hpp"
#include "Physics.hpp"
#include "Actor.hpp"
#include "Converter.hpp"
#include "MeshFilter.hpp"


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

/** radius Getter*/
float SphereCollider::getRadius()
{
	return radius;
}

/** radius Setter*/
void SphereCollider::setRadius(float newRadius)
{
	this->radius = newRadius;

	// Update PhysX scene
	PxSphereGeometry sphereGeometry;
	shape->getSphereGeometry(sphereGeometry);

	sphereGeometry.radius = newRadius;

	shape->setGeometry(sphereGeometry);

}

/** Init component override. Create a new Sphere Shape in the PhysX scene. */
void SphereCollider::init()
{
	// Deserializing
    if(initWithData)
    {
        shape = Physics::createSphereCollider(radius,center,getActor());
        
        // The physics material is set but it's not yet linked to the shape
        setPhysicsMaterial(getPhysicsMaterial());
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

	shared_ptr<Component> SphereCollider::clone() {
        shared_ptr<SphereCollider> compClone = make_shared<SphereCollider>(radius,center);
        compClone->setPhysicsMaterial(getPhysicsMaterial());
        return compClone;
    };

/** Get a description for the current component*/
shared_ptr<ComponentDescription> SphereCollider::getComponentDescription()
{
    PxSphereGeometry geo;
    shape->getSphereGeometry(geo);
    
    return make_shared<SphereColliderDescription>(geo.radius);
}

/** Deserialize a component description into this collider */
void SphereCollider::deserialize(shared_ptr<ComponentDescription> desc)
{
    shared_ptr<SphereColliderDescription> sphereColDesc = dynamic_pointer_cast<SphereColliderDescription>(desc);
    this->radius = sphereColDesc->radius;
    this->center = sphereColDesc->center;
    initWithData = true;
}
