#pragma once
#include "Component.hpp"

class Mesh;
class MeshComponent :
	public Component
#ifdef GUINITY_DEBUG
	, public StaticCounter<MeshComponent>
#endif
{
public:
	MeshComponent();
	virtual ~MeshComponent();


	void setMesh(shared_ptr<Mesh> mesh);

	shared_ptr<Mesh> mesh;

	virtual shared_ptr<ComponentDescription> getComponentDescription() override;

	virtual shared_ptr<Component> clone() override{ shared_ptr<MeshComponent> compClone = make_shared<MeshComponent>(); return compClone; };

	void deserialize(shared_ptr<ComponentDescription> desc) override;

	void getBoxSize(shared_ptr<Actor> actor, PxVec3& boxSize, PxVec3& center);

	void getSphereSize(shared_ptr<Actor> actor, float& radius, PxVec3& center);

	void getCapsuleGeometry(shared_ptr<Actor>actor, float &radius, float &halfHeight, RotateAxis&orientation, PxVec3& center);
};

