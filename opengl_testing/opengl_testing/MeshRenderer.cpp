#include "MeshRenderer.hpp"


MeshRenderer::MeshRenderer(shared_ptr<Mesh> mesh, shared_ptr<Material> m)
{
	this->material = m;
	this->mesh = mesh;

#ifdef GUINITY_DEBUG
	nCount++;
#endif
}


MeshRenderer::~MeshRenderer()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "MeshRenderer destroyed (" << nCount << " remaining)" << endl;
#endif
	
}
