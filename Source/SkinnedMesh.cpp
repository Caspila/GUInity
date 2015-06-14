//
//  Skin.cpp
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-06-06.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "SkinnedMesh.hpp"
#include "GraphicsSystem.hpp"
#include "Time.hpp"
#include <math.h>
/** Adds a new vertex to the mesh */


void SkinnedMesh::setVerticesWeight(vector<VertexBone> weights)
{
    this->weights = weights;
    
    for(int i = 0; i < meshVertices.size(); i++)
    {
        vector<VertexBoneWeight> vb = weights[i].weights;
        
//        weights2.push_back(VertexBoneVec(0,1,2,0.1,0.1,0.1));//,vb[0].weight,vb[1].weight,vb[2].weight));
          weights2.push_back(VertexBoneVec(vb[0].boneIndex,vb[1].boneIndex,vb[2].boneIndex,vb[0].weight,vb[1].weight,vb[2].weight));
        cout << vb[0].boneIndex << " " << vb[0].weight << "\n";
    }
    
//    for(int i = 0; i < weights.size(); i++)
//    {
//        cout << "Vertex: " << i << endl;
//        for(int j= 0; j < weights[i].size(); j++)
//        {
//            cout << "Bone ("<<j<<")"<<":"<<weights[i][j]<<endl;
//        }
//    }
    
//    vector<vector<float>> w(meshVertices.size(),vector<float>(10));
//    
//    for(int i = 0 ; i < meshVertices.size(); i++)
//    {
//        test.push_back(1);
//        
//        for(int j = 0; j < 10; j++)
//        {
//            w[i][j] = 1.0f;
//        }
//    }
//    float** z = new float*[meshVertices.size()];
//    for (int i =0; i < meshVertices.size(); i++) {
//        z[i] = new float[10];
//    }
//    
//    this->weights = w;
//    
    boneVBO = 0;
    GraphicsSystem::getInstance()->generateBuffer(1,boneVBO,GL_ARRAY_BUFFER,nBones * sizeof(VertexBoneVec) * meshVertices.size(),& this->weights2[0],GL_STATIC_DRAW);
//
//    testVBO = 0;
//    GraphicsSystem::getInstance()->generateBuffer(1,testVBO,GL_ARRAY_BUFFER,sizeof(float)*meshVertices.size()*4,& this->test,GL_STATIC_DRAW);
}

GLuint SkinnedMesh::getBonesVBO()
{
    return boneVBO;
}

GLuint SkinnedMesh::getTestVBO()
{
    return testVBO;
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

void SkinnedMesh::setAnimation(Animation animation)
{
    this->animation = animation;
    
//    std::vector<glm::mat4> evaluation;
//    for(int i = 6; i < 19; i++)
//        animation.evaluateAnimation(i, evaluation);
//    
//    cout << "bla " << endl;
}

void SkinnedMesh::tickDelta()
{
//    boneTransform[0] = glm::translate(glm::vec3(xDelta,0,0));
//    for(int i= 0; i < 10; i++)
//        boneTransform[i] = glm::mat4(1.0);
//    boneTransform[0] = glm::translate(glm::vec3(xDelta,0,0));
//        boneTransform[1] = glm::translate(glm::vec3(2*xDelta,0,0));
//            boneTransform[2] = glm::translate(glm::vec3(xDelta,0,0));
    xDelta +=  1*Time::deltaTime;
    
    vector<glm::mat4> eval;
    animation.evaluateAnimation(xDelta, eval);
    
    for(int i = 0; i < eval.size(); i++)
    {
        boneTransform[i] = eval[i];
    }
    
    xDelta = fmod(xDelta, 18);
    if(xDelta < 6.0f)
        xDelta = 6;
//    xDelta = 18;
}

glm::mat4* SkinnedMesh::getDeltaPos()
{
    tickDelta();
    return boneTransform;
}