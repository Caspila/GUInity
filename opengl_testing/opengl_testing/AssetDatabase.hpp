//
//  File.h
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2014-12-30.
//  Copyright (c) 2014 Guilherme Cunha. All rights reserved.
//

#ifndef __opengl_testing_mag__File__
#define __opengl_testing_mag__File__

#include <iostream>
#include "MeshImporter.hpp"
#include <map>
#include "Asset.hpp"
#include "Mesh.hpp"

class Shader;
class Material;
class Shader;
class Texture;


class AssetDatabase
{
    static MeshImporter meshImporter;

public:
    static unsigned int currentID;
    
    static std::map<unsigned int,shared_ptr<Asset>> idToAsset;
    
    static void init();
    static void shutdown();
    
    static shared_ptr<Shader> createShader(string vsFilename, string fsFilename);
    static shared_ptr<Material> createMaterial(shared_ptr<Shader> shader);
    static shared_ptr<Mesh> createMeshFromFBX(string filename);
    static shared_ptr<Mesh> createMeshFromOBJ(string filename);
    static shared_ptr<Mesh> createMesh();
    
    static shared_ptr<Mesh> createMesh(vector<glm::vec3> vertices,vector<int> usedIndex,vector<int> usedTris);
    
    static shared_ptr<Mesh> createMesh(vector<MeshVertex> vertex, vector<unsigned short> triangles);
    static shared_ptr<Texture> createTexture(string filename);
    
  
    
    template <typename T>
    static void assignCurrentID(T asset);
    
};


#endif /* defined(__opengl_testing_mag__File__) */
