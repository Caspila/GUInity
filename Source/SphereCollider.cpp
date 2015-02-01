#include "SphereCollider.hpp"
#include "Physics.hpp"
#include "Actor.hpp"
#include "Converter.hpp"

SphereCollider::SphereCollider(float radius, PxVec3 center = PxVec3(0,0,0))
{
    this->radius = radius;
    this->center = center;
    
    initWithData = true;
    
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

SphereCollider::SphereCollider()
{

    initWithData = false;
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}


SphereCollider::~SphereCollider()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "SphereCollider destroyed (" << nCount << " remaining)" << endl;
#endif
}



void SphereCollider::init()
{
    if(initWithData)
        shape = Physics::createSphereCollider(radius,center,getActor());
    else
    {
        shared_ptr<MeshFilter> meshFilter = getActor()->GetComponent<MeshFilter>();
        
        radius = 0.5f;
        center = PxVec3(0,0,0);
        
        if(meshFilter)
            meshFilter->getSphereSize(getActor(), radius, center);
            
        shape = Physics::createSphereCollider(radius,center,getActor());
    }
}

shared_ptr<ComponentDescription> SphereCollider::getComponentDescription()
{
    PxSphereGeometry geo;
    shape->getSphereGeometry(geo);
    
    return make_shared<SphereColliderDescription>(geo.radius);
}

void SphereCollider::deserialize(shared_ptr<ComponentDescription> desc)
{
    shared_ptr<SphereColliderDescription> sphereColDesc = dynamic_pointer_cast<SphereColliderDescription>(desc);
    this->radius = sphereColDesc->radius;
    this->center = sphereColDesc->center;
    initWithData = true;
}

float SphereCollider::getRadius()
{
	return radius;
}
void SphereCollider::setRadius(float newRadius)
{
	this->radius = newRadius;

	PxSphereGeometry sphereGeometry;
	shape->getSphereGeometry(sphereGeometry);

	sphereGeometry.radius = newRadius;

	shape->setGeometry(sphereGeometry);

}