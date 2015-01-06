//
//  SerializationStructs.cpp
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-04.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "SerializationStructs.h"
#include "Transform.hpp"
#include "Actor.hpp"

TransformDescription getTransformDescription(shared_ptr<Transform> t)

{
    return TransformDescription {t->position,t->scale,t->rotationQuat};
}

ActorDescription getActorDescription(shared_ptr<Actor> actor)
{
    return ActorDescription {actor->name, actor->isActive,actor->editorFlag,getTransformDescription(actor->transform)};
}

vector<shared_ptr<ComponentDescription>> getActorComponentsDescription(shared_ptr<Actor> actor)
{
    vector<shared_ptr<ComponentDescription>> descs;
    
    for(auto&x : actor->components)
        descs.push_back((x->getComponentDescription()));
    
    return descs;
}