#pragma once

#include "Module.h"
#include "Mesh.h"
#include "Material.h"

class MeshRenderer
{
public:
	MeshRenderer(shared_ptr<Mesh> mesh, shared_ptr<Material> m);
	~MeshRenderer();

	shared_ptr<Mesh> mesh;
	shared_ptr<Material> material;

};

