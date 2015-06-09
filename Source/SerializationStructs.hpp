//
//  SerializationStructs.h
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-04.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __opengl_testing_mag__SerializationStructs__
#define __opengl_testing_mag__SerializationStructs__

#include <iostream>
#include "Module.hpp"
#include <glm/common.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>
#include "Enums.hpp"
#include <PxPhysics.h>

using namespace physx;

class Transform;
class Actor;
class ComponentDescription;

struct TransformDescription
{
    glm::vec3 position, scale;
    glm::quat rotation;
};

struct ActorDescription
{
    string name;
    bool isActive;
    bool editorFlag;
    TransformDescription transform;
    
    vector<shared_ptr<ComponentDescription>> components;
    vector<ActorDescription> children;
};

enum ComponentType
{ COMPONENT_MESHFILTER = 0, COMPONENT_MESHRENDERER = 1, COMPONENT_CAMERA = 2, COMPONENT_RIGIDBODY = 3, COMPONENT_RIGIDSTATIC = 4, COMPONENT_LIGHT = 5, COMPONENT_BOXCOLLIDER=6, COMPONENT_SPHERECOLLIDER=7, COMPONENT_CAPSULECOLLIDER=8, COMPONENT_FONTMESH=9};

class ComponentDescription
{
public:
    ComponentType type;
    ComponentDescription() {};
    virtual ~ComponentDescription() {};
};

class MeshFilterDescription : public ComponentDescription
{
public:
    
    int meshID;
    MeshFilterDescription(){};
    
    MeshFilterDescription(int id) : meshID {id} { type = COMPONENT_MESHFILTER;};
    virtual ~MeshFilterDescription() {};
};
class MeshRendererDescription : public ComponentDescription
{
public:
    int materialID;
    
    
    MeshRendererDescription(){};
    MeshRendererDescription(int id) : materialID {id} {type = COMPONENT_MESHRENDERER;};
    virtual ~MeshRendererDescription() {};
};

class LightDescription : public ComponentDescription
{
public:
    glm::vec3 color;
    
    LightDescription(){};
    LightDescription(glm::vec3 c) : color {c} {type = COMPONENT_LIGHT;};
    virtual ~LightDescription() {};
};

class CameraDescription : public ComponentDescription
{
public:
    float nearClipPlane, farClipPlane;
	float fov;
	float ratio;
    
    CameraDescription(){};
    CameraDescription(float  near, float far, float f, float r) : nearClipPlane {near},farClipPlane {far},fov{f}, ratio{r}   {type = COMPONENT_CAMERA;};
    virtual ~CameraDescription() {};
};


class RigidBodyDescription : public ComponentDescription
{
public:
    bool isKinematic;
    int lockConstraints;
    bool gravityEnabled;
    
    RigidBodyDescription(){};
    RigidBodyDescription(bool  isKinematic, int lockConstraints, bool gravityEnabled ) : isKinematic {isKinematic}, lockConstraints{lockConstraints}, gravityEnabled{gravityEnabled} {type = COMPONENT_RIGIDBODY;};
    virtual ~RigidBodyDescription() {};
};

class RigidStaticDescription : public ComponentDescription
{
public:
    
    RigidStaticDescription() {type = COMPONENT_RIGIDSTATIC;};
    virtual ~RigidStaticDescription() {};
};

class ColliderDescription : public ComponentDescription
{
    
public:
    PxVec3 center;
    bool isTrigger;
    bool isQueryOnly;
    int physicsMaterialID;
    ColliderDescription() {}
    ColliderDescription(PxVec3 center, bool isTrigger, bool isQueryOnly,int physicsMaterialID) : center {center}, isTrigger {isTrigger}, isQueryOnly {isQueryOnly}, physicsMaterialID{physicsMaterialID} {};
    virtual ~ColliderDescription() {};
};

class BoxColliderDescription : public ColliderDescription
{
public:
    PxVec3 halfExtent;
    
    BoxColliderDescription() {}
    BoxColliderDescription(PxVec3 center, bool isTrigger, bool isQueryOnly, int physicsMaterialID,PxVec3 halfExt) :
    ColliderDescription(center,isTrigger,isQueryOnly,physicsMaterialID),
    halfExtent {halfExt}
    {type = COMPONENT_BOXCOLLIDER;};
    virtual ~BoxColliderDescription() {};
};
class SphereColliderDescription : public ColliderDescription
{
public:
    float radius;
    
    SphereColliderDescription() {}
    SphereColliderDescription(PxVec3 center, bool isTrigger, bool isQueryOnly, int physicsMaterialID,float r) :
    ColliderDescription(center,isTrigger,isQueryOnly,physicsMaterialID),
    radius {r}
    
    {type = COMPONENT_SPHERECOLLIDER;};
    virtual ~SphereColliderDescription() {};
};
class CapsuleColliderDescription : public ColliderDescription
{
public:
    float radius;
    float halfHeight;
    RotateAxis orientation;
    
    CapsuleColliderDescription() {}
    CapsuleColliderDescription(PxVec3 center, bool isTrigger, bool isQueryOnly, int physicsMaterialID, float halfH,float r, RotateAxis o) :ColliderDescription(center,isTrigger,isQueryOnly,physicsMaterialID),
    halfHeight{halfH},
    radius {r}
    { orientation = o;type = COMPONENT_CAPSULECOLLIDER;};
    virtual ~CapsuleColliderDescription() {};
};

class FontMeshDescription : public ComponentDescription
{
public:
    string text;
    int fontID;
    
    FontMeshDescription() {}
    FontMeshDescription(string text, int fontID ) :text {text}, fontID{fontID}    {;type = COMPONENT_FONTMESH;};
    virtual ~FontMeshDescription() {};
};



TransformDescription getTransformDescription(shared_ptr<Transform> t);
ActorDescription getActorDescription(shared_ptr<Actor> actor);
vector<shared_ptr<ComponentDescription>> getActorComponentsDescription(shared_ptr<Actor> actor);

#endif /* defined(__opengl_testing_mag__SerializationStructs__) */

