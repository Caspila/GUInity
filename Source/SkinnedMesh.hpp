//  SKINNED MESH IS CURRENTLY UNDER DEVELOPMENT
//  SKINNED MESH IS CURRENTLY UNDER DEVELOPMENT
//  SKINNED MESH IS CURRENTLY UNDER DEVELOPMENT
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
#include "Animation.hpp"
#include <queue>
#include <algorithm>

using namespace std;



struct VertexBoneVec
{
    glm::vec3 boneIndex;
    glm::vec3 weight;
//    int boneIndex;
//    float weight;
    
public:
//    VertexBoneWeight() : boneIndex{0}, weight{0}
//    {
//    }
    VertexBoneVec(int boneIndex1,int boneIndex2, int boneIndex3,
                     float weight1,float weight2,float weight3) : boneIndex{boneIndex1,boneIndex2,boneIndex3}, weight{weight1,weight2,weight3}
    {
    }
};

struct VertexBoneWeight
{
    int boneIndex;
    float weight;
    
public:
    VertexBoneWeight() : boneIndex{0}, weight{0}
    {
    }
    VertexBoneWeight(int boneIndex,float weight) : boneIndex{boneIndex}, weight{weight}
    {
    }
};

struct VertexBoneWeightComparer
{
    inline bool operator() (const VertexBoneWeight& struct1, const VertexBoneWeight& struct2)
    {
        return (struct1.weight > struct2.weight);
    }
};

struct VertexBone
{
    std::vector<VertexBoneWeight> weights;

    
public:

    void init(int nBones)
    {
        weights.resize(nBones);
    }
    void addWeight(int boneIndex, float weight)
    {
        weights.at(boneIndex) = VertexBoneWeight(boneIndex,weight);
    }
    void sortWeight()
    {
        std::sort(weights.begin(),weights.end(),VertexBoneWeightComparer());
    }
    
};

class SkinnedMesh : public Mesh
{
private:
    vector<VertexBone> weights;
    vector<VertexBoneVec> weights2;
    vector<glm::mat4> initialPos;
    
    vector<float> test;
    
    int nBones;
    Animation animation;
    
    glm::mat4 boneTransform[10];
    float xDelta = 0.0f;
    
    GLuint boneVBO;
    
    /** Vertex data array*/
//	GLuint animbo;
public:
    SkinnedMesh();

    virtual ~SkinnedMesh();
    
    
    void setNBones(int nBones);
    int getNBones();
    
    GLuint getTestVBO();
    GLuint getBonesVBO();
    
    void setVerticesWeight(vector<VertexBone> weights);
    void setInitialPosition(vector<glm::mat4> initialPos);

    
    void setAnimation(Animation animation);
    
//    GLuint getSkelArrayID() {return animbo;}
    
    void tickDelta();
    glm::mat4* getDeltaPos();
    
};

#endif /* defined(__GUInity_MacOS__Skin__) */
