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
};

enum ComponentType
{ COMPONENT_MESHFILTER = 0, COMPONENT_MESHRENDERER = 1, COMPONENT_CAMERA = 2, COMPONENT_RIGIDBODY = 3, COMPONENT_RIGIDSTATIC = 4, COMPONENT_LIGHT = 5, COMPONENT_BOXCOLLIDER=6, COMPONENT_SPHERECOLLIDER=7, COMPONENT_CAPSULECOLLIDER=8};

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
    
    RigidBodyDescription(){};
    RigidBodyDescription(bool  kinematic) : isKinematic {kinematic} {type = COMPONENT_RIGIDBODY;};
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
    ColliderDescription(){};
    virtual ~ColliderDescription() {};
};

class BoxColliderDescription : public ColliderDescription
{
public:
    PxVec3 halfExtent;
    
    BoxColliderDescription(){};
    BoxColliderDescription(PxVec3 halfExt) : halfExtent {halfExt} {type = COMPONENT_BOXCOLLIDER;};
    virtual ~BoxColliderDescription() {};
};
class SphereColliderDescription : public ColliderDescription
{
public:
    float radius;
    
    SphereColliderDescription(){};
    SphereColliderDescription(float r) : radius {r} {type = COMPONENT_SPHERECOLLIDER;};
    virtual ~SphereColliderDescription() {};
};
class CapsuleColliderDescription : public ColliderDescription
{
public:
    float radius;
    float halfHeight;
    RotateAxis orientation;
    
    CapsuleColliderDescription(){};
    CapsuleColliderDescription(float halfH,float r, RotateAxis o) :halfHeight{halfH}, radius {r} { orientation = o;type = COMPONENT_CAPSULECOLLIDER;};
    virtual ~CapsuleColliderDescription() {};
};



TransformDescription getTransformDescription(shared_ptr<Transform> t);
ActorDescription getActorDescription(shared_ptr<Actor> actor);
vector<shared_ptr<ComponentDescription>> getActorComponentsDescription(shared_ptr<Actor> actor);

#endif /* defined(__opengl_testing_mag__SerializationStructs__) */

