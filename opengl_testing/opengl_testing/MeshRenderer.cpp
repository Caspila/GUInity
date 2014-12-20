#include "MeshRenderer.h"


MeshRenderer::MeshRenderer(shared_ptr<Mesh> mesh, shared_ptr<Material> m)
{
	this->material = m;
	this->mesh = mesh;
	
}


MeshRenderer::~MeshRenderer()
{
	cout << "MeshRenderer destroyed" << endl;
}
