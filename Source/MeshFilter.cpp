#include "MeshFilter.hpp"
#include "Mesh.hpp"
#include "AssetDatabase.hpp"
#include "Actor.hpp"
#include "Converter.hpp"

/** Default Constructor */
MeshFilter::MeshFilter()
{
    
}

/** Default Destructor. Virtual because it's child class. */
MeshFilter::~MeshFilter()
{
}

/** Clones current component (Prototype Design Pattern)
 @return shared_ptr to cloned MeshFilter Component
 */
shared_ptr<Component> MeshFilter::clone()
{
    shared_ptr<MeshFilter> compClone = make_shared<MeshFilter>();
    
    compClone->setMesh(getMesh());
    
    return compClone;
}

