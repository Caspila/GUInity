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
#include <boost/crc.hpp>

class Shader;
class Material;
class Shader;
class Texture;


class AssetDatabase
{
    static MeshImporter meshImporter;

    //static int getCRC(string filename);
    
public:
    static unsigned int currentID;
    
    static std::map<unsigned int,shared_ptr<Asset>> idToAsset;
    static std::map<string,shared_ptr<Asset>> nameToAsset;
    
    static void init();
    static void shutdown();
    static void loadAllMetaFiles();
    static void loadFile(string fullPath);
    
    static shared_ptr<Shader> createShader(string name, string vsFilename, string fsFilename);
    static shared_ptr<Material> createMaterial(string name, shared_ptr<Shader> shader);
    static shared_ptr<Mesh> createMeshFromFBX(string filename);
    static shared_ptr<Mesh> createMeshFromOBJ(string filename);
    static shared_ptr<Mesh> createMesh();
    
    static shared_ptr<Mesh> createMesh(vector<glm::vec3> vertices,vector<int> usedIndex,vector<int> usedTris);
    
    static shared_ptr<Mesh> createMesh(vector<MeshVertex> vertex, vector<unsigned short> triangles);
    static shared_ptr<Texture> createTexture(string filename);
    
    static shared_ptr<Asset> getAsset(string filename);
    
    
//    template <typename T>
//    static void assignCurrentID(T asset);
//    template <typename T>
//    static void assignName(T asset, string name);
    template <typename T>
    static void assignCurrentID(T asset, string name);
    template <typename T>
    static void assignCurrentID(T asset);
    
};


#endif /* defined(__opengl_testing_mag__File__) */
