#include "MeshFilter.hpp"
#include "Mesh.hpp"
#include "AssetDatabase.hpp"
#include "Actor.hpp"
#include "Converter.hpp"

MeshFilter::MeshFilter()
{

}


MeshFilter::~MeshFilter()
{
}

shared_ptr<Component> MeshFilter::clone()
{
    shared_ptr<MeshFilter> compClone = make_shared<MeshFilter>();

    compClone->setMesh(getMesh());
    
    return compClone;
}

