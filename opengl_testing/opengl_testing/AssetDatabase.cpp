//
//  File.cpp
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2014-12-30.
//  Copyright (c) 2014 Guilherme Cunha. All rights reserved.
//

#include "AssetDatabase.hpp"
#include "Asset.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "Shader.hpp"

unsigned int AssetDatabase::currentID =0;
MeshImporter AssetDatabase::meshImporter;
std::map<unsigned int,shared_ptr<Asset>> AssetDatabase::idToAsset;


void AssetDatabase::init()
{
    meshImporter.init();
}

void AssetDatabase::shutdown()
{
    meshImporter.shutdown();
}

template <typename T>
void AssetDatabase::assignCurrentID(T asset)
{
    asset->setAssetID(currentID);
    
    idToAsset[currentID] = asset;
    
    currentID++;
}


shared_ptr<Shader> AssetDatabase::createShader(string vsFilename, string fsFilename)
{
 
    shared_ptr<Shader> shader = make_shared<Shader>(vsFilename,fsFilename);
    assignCurrentID(shader);
    
    return shader;
}

shared_ptr<Material> AssetDatabase::createMaterial(shared_ptr<Shader> shader)
{
    shared_ptr<Material> material = make_shared<Material>(shader);
    assignCurrentID(material);
    
    return material;
}

 shared_ptr<Mesh> AssetDatabase::createMeshFromFBX(string filename)
{
    shared_ptr<Mesh> mesh = meshImporter.importFbxMesh(filename);
    assignCurrentID(mesh);
    
    return mesh;
}
 shared_ptr<Mesh> AssetDatabase::createMeshFromOBJ(string filename)
{
    shared_ptr<Mesh> mesh = meshImporter.importObjMesh(filename);
    assignCurrentID(mesh);
    
    return mesh;
}
 shared_ptr<Mesh> AssetDatabase::createMesh()
{
    shared_ptr<Mesh> mesh = make_shared<Mesh>();
    assignCurrentID(mesh);
    
    return mesh;
}