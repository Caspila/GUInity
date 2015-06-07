//
//  Skin.h
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-06-06.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __GUInity_MacOS__Skin__
#define __GUInity_MacOS__Skin__

#include <iostream>
#include "Mesh.hpp"
#include <glm/glm.hpp>

using namespace std;

class SkinnedMesh : public Mesh
{
private:
    vector<vector<float>> weights;
    vector<glm::mat4> initialPos;
    int nBones;
    
public:
    SkinnedMesh() {};
    virtual ~SkinnedMesh() {};
    
    
    void setNBones(int nBones);
    int getNBones();
    
    void setVerticesWeight(vector<vector<float>> weights);
    void setInitialPosition(vector<glm::mat4> initialPos);

    
};

#endif /* defined(__GUInity_MacOS__Skin__) */
