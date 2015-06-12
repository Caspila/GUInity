//
//  Animation.h
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-06-11.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __GUInity_MacOS__Animation__
#define __GUInity_MacOS__Animation__

#include <iostream>
#include "Animation.hpp"
#include "AnimationCurve.hpp"
#include <map>
#include "Enums.hpp"


class Animation
{
public:
    Animation() {}
    virtual ~Animation() {}
    
    std::vector<std::map<CurveAnimationType,AnimationCurve>> animationCurveMap;
    
    int nBones;
    
    int getNBones() { return nBones;}
    void setNBones(int nBones) { this->nBones = nBones;}
    
    void addAnimationCurveNode(std::map<CurveAnimationType,AnimationCurve> node)
    {
        animationCurveMap.push_back(node);
    }
    
    
    void evaluateAnimation(float time, std::vector<glm::mat4>& evaluation)
    {
        if(evaluation.size() < animationCurveMap.size())
            evaluation.resize(animationCurveMap.size());
        
        for (int i = 0; i < animationCurveMap.size(); i++) {
            evaluation[i] = evaluateAnimation(i, time);
        }
    }
    
    glm::mat4 evaluateAnimation(int nodeIndex, float time)
    {   
        std::map<CurveAnimationType,AnimationCurve> node = animationCurveMap[nodeIndex];
        
        glm::vec3 pos;
        auto it = node.find(CurveAnimationType::X_MOVE);
        if(it!= node.end())
            pos.x = it->second.evaluate(time);
        
        it = node.find(CurveAnimationType::Y_MOVE);
        if(it!= node.end())
            pos.y = it->second.evaluate(time);
        
        it = node.find(CurveAnimationType::Z_MOVE);
        if(it!= node.end())
            pos.z = it->second.evaluate(time);
        
        
        
        glm::vec3 rot;
        it = node.find(CurveAnimationType::X_ROTATE);
        if(it!= node.end())
            rot.x = it->second.evaluate(time);
        
        it = node.find(CurveAnimationType::Y_ROTATE);
        if(it!= node.end())
            rot.y = it->second.evaluate(time);
        
        it = node.find( CurveAnimationType::Z_ROTATE);
        if(it!= node.end())
            rot.z = it->second.evaluate(time);
        glm::quat rotQuat(rot);
        
        
        glm::vec3 scale;
        it = node.find( CurveAnimationType::X_SCALE);
        if(it!= node.end())
            scale.x = it->second.evaluate(time);
        
        it = node.find( CurveAnimationType::Y_SCALE);
        if(it!= node.end())
            scale.y = it->second.evaluate(time);
        
        it = node.find( CurveAnimationType::Z_SCALE);
        if(it!= node.end())
            scale.z = it->second.evaluate(time);
        
//        if(nodeIndex==0)
//            std::cout << "NodeIndex:" <<nodeIndex << "  " << pos.x << "," << pos.y << "," << pos.z << std::endl;
//        
        return glm::translate(pos) * (glm::mat4)(rotQuat) * glm::scale(scale) ;
    }
};

#endif /* defined(__GUInity_MacOS__Animation__) */
