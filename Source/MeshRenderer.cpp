#include "MeshRenderer.hpp"
#include "Actor.hpp"
#include "MeshFilter.hpp"
#include "GraphicsSystem.hpp"
#include "Material.hpp"
#include "AssetDatabase.hpp"

/** Default Constructor */
MeshRenderer::MeshRenderer()// shared_ptr<Mesh> mesh, shared_ptr<Material> m)
{
	//this->material = m;
	//this->mesh = mesh;
    
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

/** Default Destructor. Virtual cause it's child class */
MeshRenderer::~MeshRenderer()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "MeshRenderer Component destroyed (" << nCount << " remaining)" << endl;
#endif
	
}

/** Component init override. Tries to get a MeshComponent from the owner Actor and notifies that a new MeshRenderer has been created */
void MeshRenderer::init()
{
    
	this->meshComponent = getActor()->GetComponent<MeshComponent>();
    
	MeshRenderer::notify(ComponentEventType::NewMeshRenderer, shared_from_this(),getActor()->getEditorFlag());
}

/** Component destroy. Notifies this MeshRenderer has been destroyed */
void MeshRenderer::destroy()
{
 	MeshRenderer::notify(ComponentEventType::RemovedMeshRenderer, shared_from_this(),getActor()->getEditorFlag());
}
/** material setter */
void MeshRenderer::setMaterial(shared_ptr<Material> material)
{
    this->material = material;
}
/** material getter */
shared_ptr<Material> MeshRenderer::getMaterial()
{
    return material;
}
/** meshComponent setter */
void MeshRenderer::setMeshComponent(shared_ptr<MeshComponent> meshComponent)
{
    this->meshComponent = meshComponent;
}
/** meshComponent getter */
shared_ptr<MeshComponent> MeshRenderer::getMeshComponent()
{
    return meshComponent.lock();
}

/** Clones current component (Prototype Design Pattern)
 @return shared_ptr to cloned MeshRenderer Component
 */
shared_ptr<Component> MeshRenderer::clone()
{
    shared_ptr<MeshRenderer> compClone = make_shared<MeshRenderer>();
    
    compClone->setMaterial(getMaterial());
    
    return compClone;
}

/** Creates a description for the Component*/

shared_ptr<ComponentDescription> MeshRenderer::getComponentDescription()
{
    return make_shared<MeshRendererDescription>(material->getAssetID());
}

/** Deserializes a description to a Component */
void MeshRenderer::deserialize(shared_ptr<ComponentDescription> desc)
{
    shared_ptr<MeshRendererDescription> meshRendDesc = dynamic_pointer_cast<MeshRendererDescription>(desc);
    
    cout << "MeshRendererDesc material id" << meshRendDesc->materialID << endl;
    
	material = AssetDatabase::getAsset<Material>(meshRendDesc->materialID);
    
}

