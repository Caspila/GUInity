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

	this->meshComponent = getActor()->GetComponent<MeshComponent>();

//	GraphicsSystem::getInstance().allMeshRenderer.push_back(shared_from_this());

	MeshRenderer::notify(ComponentEventType::NewMeshRenderer, shared_from_this(),getActor()->getEditorFlag());
}

void MeshRenderer::setMaterial(shared_ptr<Material> material)
{
    this->material = material;
}

shared_ptr<Material> MeshRenderer::getMaterial()
{
    return material;
}

shared_ptr<ComponentDescription> MeshRenderer::getComponentDescription()
{
    return make_shared<MeshRendererDescription>(material->getAssetID());
}

void MeshRenderer::deserialize(shared_ptr<ComponentDescription> desc)
{
    shared_ptr<MeshRendererDescription> meshRendDesc = dynamic_pointer_cast<MeshRendererDescription>(desc);
    
    cout << "MeshRendererDesc material id" << meshRendDesc->materialID << endl;
    
    
	material = dynamic_pointer_cast<Material>(AssetDatabase::getAsset(meshRendDesc->materialID));
    
}

shared_ptr<Component> MeshRenderer::clone()
{
    shared_ptr<MeshRenderer> compClone = make_shared<MeshRenderer>();
    
    compClone->setMaterial(getMaterial());
    
    return compClone;
}