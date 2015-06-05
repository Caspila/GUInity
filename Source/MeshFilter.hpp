#pragma once
#include "ScriptComponent.hpp"
#include "Component.hpp"
#include <PxPhysicsAPI.h>
#include "MeshComponent.hpp"



using namespace physx;

//class Mesh;
class Component;

class MeshFilter :
	public MeshComponent
//#ifdef GUINITY_DEBUG
//	, public StaticCounter<MeshFilter>
//#endif
{
public:
	MeshFilter();
	virtual ~MeshFilter();

    virtual shared_ptr<Component> clone() override;

        
};

