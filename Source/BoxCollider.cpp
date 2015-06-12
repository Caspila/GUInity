#include "BoxCollider.hpp"
#include "Physics.hpp"
#include "Actor.hpp"
#include "Converter.hpp"
#include "MeshFilter.hpp"
#include "PhysicsMaterial.hpp"
#include "AssetDatabase.hpp"

using namespace physx;

/** Default Constructor */
BoxCollider::BoxCollider()
{
    setCopyMode(false);
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

/** Deserialization Constructor */
BoxCollider::BoxCollider(PxVec3 halfExtent, PxVec3 center)
{
    this->halfExtent = halfExtent;
    this->center = center;
    setCopyMode(true);
    
    
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

/** Default Destructor*/
BoxCollider::~BoxCollider()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "BoxCollider destroyed (" << nCount << " remaining)" << endl;
#endif
}

/** Init component override. Create a new Box Shape in the PhysX scene. */
void BoxCollider::init()
{
    Component::init();
    
	// Deserializing
    if(initWithData)
    {
        shape = Physics::createBoxCollider(halfExtent,center,getActor());
        
        // The physics material is set but it's not yet linked to the shape
        if(physicsMaterial!=nullptr)
            setPhysicsMaterial(getPhysicsMaterial());
        
        setHalfExtent(halfExtent);
        
    }
	// Create new
    else
    {
        shared_ptr<MeshFilter> meshFilter = getActor()->GetComponent<MeshFilter>();
        
        center = PxVec3(0, 0, 0);
        halfExtent= PxVec3(0.5f, 0.5f, 0.5f);
        
        if(meshFilter)
            meshFilter->getBoxSize(getActor(), halfExtent,center);
        
        shape = Physics::createBoxCollider(halfExtent,center,getActor());
        
        // Sets the material as the default one
        Collider::init();
    }
    
}

/** halfExtent getter
 @return half extent of the AABB
 */
PxVec3 BoxCollider::getHalfExtent() const
{
    return halfExtent;
}
/** halfExtent setter
 @param [in] halfExtent half extent of the AABB
 */
void BoxCollider::setHalfExtent(PxVec3 halfExtent)
{
    this->halfExtent = halfExtent;
    
    if(shape)
    {
        // Update PhysX scene
        PxBoxGeometry boxGeometry;
        
        shape->getBoxGeometry(boxGeometry);
        
        boxGeometry.halfExtents = halfExtent;
        
        shape->setGeometry(boxGeometry);
    }
}

/** Clones current component (Prototype Design Pattern)
 @return shared_ptr to cloned BoxCollider Component
 */
shared_ptr<Component> BoxCollider::clone()
{
    shared_ptr<BoxCollider> compClone = make_shared<BoxCollider>(halfExtent, center);
    
    if(physicsMaterial!=nullptr)
        compClone->setPhysicsMaterial(getPhysicsMaterial());
    return compClone;
}

/** Creates a description for the Component*/
shared_ptr<ComponentDescription> BoxCollider::getComponentDescription()
{
    return make_shared<BoxColliderDescription>(center,isTrigger,isQueryOnly,getPhysicsMaterial()->getAssetID(),halfExtent);
}

/** Deserializes a description to a Component */
void BoxCollider::deserialize(shared_ptr<ComponentDescription> desc)
{
    
    shared_ptr<BoxColliderDescription> boxColDesc = dynamic_pointer_cast<BoxColliderDescription>(desc);
    this->halfExtent = boxColDesc->halfExtent;
    this->center = boxColDesc->center;
    this->isQueryOnly = boxColDesc->isQueryOnly;
    this->isTrigger = boxColDesc->isTrigger;
    
    setPhysicsMaterial(AssetDatabase::getAsset<PhysicsMaterial>(boxColDesc->physicsMaterialID));

    setCopyMode(true);
}