#pragma once
#include "Component.hpp"

class Mesh;

/** MeshComponent is a Component makes a reference to a Mesh asset. This is important to prevent the same Mesh to live multiple times in memory.
	This class is inherited	used by MeshFilter and FontMesh
*/
class MeshComponent :
	public Component
#ifdef GUINITY_DEBUG
	, public StaticCounter<MeshComponent>
#endif
{
protected:
	/** The Mesh Asset*/
	shared_ptr<Mesh> mesh;

public:
	/** Default Constructor*/
	MeshComponent();
	/** Default Destructor. Virtual because this is a parent class*/
	virtual ~MeshComponent();

	/** mesh Getter */
	void setMesh(shared_ptr<Mesh> mesh);
	/** mesh Setter */
	shared_ptr<Mesh> getMesh();

	/** Gets the center and the AABB size for the Actor that this component is attached to */
	void getBoxSize(shared_ptr<Actor> actor, PxVec3& boxSize, PxVec3& center);
	/** Gets the center and the radius for the Actor that this component is attached to*/
	void getSphereSize(shared_ptr<Actor> actor, float& radius, PxVec3& center);
	/** Gets the center and the capsule description for the Actor that this component is attached to*/
	void getCapsuleGeometry(shared_ptr<Actor>actor, float &radius, float &halfHeight, RotateAxis&orientation, PxVec3& center);


	/** Prototype design pattern*/
	virtual shared_ptr<Component> clone() = 0;

	/** Serialization region*/
	/** Get a description for the current component*/
	virtual shared_ptr<ComponentDescription> getComponentDescription() override;
	/** Deserialize a component description to a collider */
	void deserialize(shared_ptr<ComponentDescription> desc) override;

	
};

