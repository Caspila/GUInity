#pragma once
#include "ScriptComponent.hpp"
#include "Component.hpp"
#include <PxPhysicsAPI.h>
#include "MeshComponent.hpp"


using namespace physx;

class Mesh;

class MeshFilter :
	public MeshComponent
//#ifdef GUINITY_DEBUG
//	, public StaticCounter<MeshFilter>
//#endif
{
public:
	MeshFilter();
	virtual ~MeshFilter();

	/*void setMesh(shared_ptr<Mesh> mesh);

	shared_ptr<Mesh> mesh;
    
    virtual shared_ptr<ComponentDescription> getComponentDescription() override;
    
    virtual shared_ptr<Component> clone() override{ shared_ptr<MeshFilter> compClone = make_shared<MeshFilter>(); return compClone;} ;

    void deserialize(shared_ptr<ComponentDescription> desc) override;

    
    
    void getBoxSize(shared_ptr<Actor> actor, PxVec3& boxSize, PxVec3& center);
    
    void getSphereSize(shared_ptr<Actor> actor, float& radius, PxVec3& center);

    void getCapsuleGeometry(shared_ptr<Actor>actor,float &radius,float &halfHeight,RotateAxis&orientation, PxVec3& center);*/

    
};

