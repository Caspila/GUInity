#pragma once
#include "ScriptComponent.hpp"
#include "Component.hpp"

class Mesh;

class MeshFilter :
	public Component
#ifdef GUINITY_DEBUG
	, public StaticCounter<MeshFilter>
#endif
{
public:
	MeshFilter();
	~MeshFilter();

	void setMesh(shared_ptr<Mesh> mesh);

	shared_ptr<Mesh> mesh;
};

