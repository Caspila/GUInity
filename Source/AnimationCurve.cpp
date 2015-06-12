//
//  AnimationCurve.cpp
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-06-11.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "AnimationCurve.hpp"

//
//AnimationCurve::AnimationCurve(AnimationCurve&& other)
//{
//    keyFrames = other.keyFrames;
//}
//
//AnimationCurve & AnimationCurve::operator= ( AnimationCurve other)
//{
//    keyFrames = other.keyFrames;
//    return *this;
//}
//
//
//AnimationCurve::AnimationCurve(AnimationCurve& other)
//{
//    keyFrames = other.keyFrames;   
//}

void  AnimationCurve::addNewKeyFrame(glm::vec2 keyFrame)
{
    keyFrames.push_back(keyFrame);
}


float AnimationCurve::evaluate(float time)
{
    int index = 0;
    auto it = keyFrames.begin();
    
    while (it!=(keyFrames.end()-1)) {
        
        if (time >= (*it).x && time <= (*(it+1)).x) {
            break;
        }
        index++;
        it++;
    }
    
    float keyFrameDuration =keyFrames[index+1].x - keyFrames[index].x;
    float startTime = time - keyFrames[index].x;
    float t = startTime/keyFrameDuration;
    
    float value = glm::lerp(keyFrames[index].y,keyFrames[index+1].y,t);
    
    return value;
    
}