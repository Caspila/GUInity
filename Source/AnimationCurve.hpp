//
//  AnimationCurve.h
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-06-11.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __GUInity_MacOS__AnimationCurve__
#define __GUInity_MacOS__AnimationCurve__

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/vector_relational.hpp>
#include <glm/gtx/common.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vec3.hpp>
#include <vector>

class AnimationCurve
{
    
public:
//    AnimationCurve() {}
//    ~AnimationCurve() {}
//    AnimationCurve(AnimationCurve& other);
//    AnimationCurve(AnimationCurve&& other);
//    AnimationCurve& operator= ( AnimationCurve other);
    
    std::vector<glm::vec2> keyFrames;
    
    
    void addNewKeyFrame(glm::vec2 keyFrame);
    float evaluate(float time);
    
};

#endif
