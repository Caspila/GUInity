//
//  Skin.cpp
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-06-06.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "SkinnedMesh.hpp"
/** Adds a new vertex to the mesh */


void SkinnedMesh::setVerticesWeight(vector<vector<float>> weights)
{
    this->weights = weights;
    
    for(int i = 0; i < weights.size(); i++)
    {
        cout << "Vertex: " << i << endl;
        for(int j= 0; j < weights[i].size(); j++)
        {
            cout << "Bone ("<<j<<")"<<":"<<weights[i][j]<<endl;
        }
    }
}

void SkinnedMesh::setInitialPosition(vector<glm::mat4> initialPos)
{
    this->initialPos = initialPos;
}

void SkinnedMesh::setNBones(int nBones)
{
    this->nBones = nBones;
}
int SkinnedMesh::getNBones()
{
    return nBones;
}