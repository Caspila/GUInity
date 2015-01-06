#include "MeshRenderer.hpp"
#include "Actor.hpp"
#include "MeshFilter.hpp"
#include "GraphicsSystem.hpp"
#include "Material.hpp"
#include "AssetDatabase.hpp"

MeshRenderer::MeshRenderer()// shared_ptr<Mesh> mesh, shared_ptr<Material> m)
{
	//this->material = m;
	//this->mesh = mesh;

#ifdef GUINITY_DEBUG
	nCount++;
#endif
}


MeshRenderer::~MeshRenderer()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "MeshRenderer Component destroyed (" << nCount << " remaining)" << endl;
#endif
	
}

void MeshRenderer::init()
{

	this->meshFilter = getActor()->GetComponent<MeshFilter>();

//	GraphicsSystem::getInstance().allMeshRenderer.push_back(shared_from_this());

	MeshRenderer::notify(ComponentEventType::NewMeshRenderer, shared_from_this(),getActor()->editorFlag);
}

void MeshRenderer::setMaterial(shared_ptr<Material> material)
{
    this->material = material;
}

shared_ptr<ComponentDescription> MeshRenderer::getComponentDescription()
{
    return make_shared<MeshRendererDescription>(material->assetID);
}

void MeshRenderer::deserialize(shared_ptr<ComponentDescription> desc)
{
    shared_ptr<MeshRendererDescription> meshRendDesc = dynamic_pointer_cast<MeshRendererDescription>(desc);
    
    cout << "MeshRendererDesc material id" << meshRendDesc->materialID << endl;
    
    
    material = dynamic_pointer_cast<Material>(AssetDatabase::idToAsset[meshRendDesc->materialID]);
    
}