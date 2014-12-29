#include "MeshRenderer.hpp"
#include "Actor.hpp"
#include "MeshFilter.hpp"
#include "GraphicsSystem.hpp"

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