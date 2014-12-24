#pragma once

#include "Module.hpp"
//#include "Mesh.h"
//#include "Material.h"

class Mesh;
class Material;

class MeshRenderer
#ifdef GUINITY_DEBUG
	:public StaticCounter<MeshRenderer>
#endif
{
public:
	MeshRenderer(shared_ptr<Mesh> mesh, shared_ptr<Material> m);
	~MeshRenderer();

	shared_ptr<Mesh> mesh;
	shared_ptr<Material> material;


};

