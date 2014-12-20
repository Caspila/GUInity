#pragma once

#include "Module.h"
#include "Material.h"
#include "Transform.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include <memory>
#include "ScriptComponent.h"
#include "StaticCounter.h"


class ScriptComponent;

class Actor
#ifdef GUINITY_DEBUG
: public StaticCounter<Actor>
#endif
{


public:
	Actor(string name, shared_ptr<MeshRenderer> meshRenderer);
	virtual ~Actor();

	string name;
	shared_ptr<Transform> transform;
	shared_ptr<MeshRenderer> meshRenderer;

	vector<ScriptComponent> scriptComponents;

	virtual void tick(float deltaSeconds) ;
};

