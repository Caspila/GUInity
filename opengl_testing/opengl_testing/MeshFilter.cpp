#include "MeshFilter.hpp"


MeshFilter::MeshFilter()
{

#ifdef GUINITY_DEBUG
	nCount++;
#endif
}


MeshFilter::~MeshFilter()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "MeshFilter destroyed (" << nCount << " remaining)" << endl;
#endif
}

void MeshFilter::setMesh(shared_ptr<Mesh> mesh)
{
	this->mesh = mesh;
}