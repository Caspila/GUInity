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
	shared_ptr<Mesh> getMesh() const;

	/** Gets the center and the AABB size for the Actor that this component is attached to */
	void getBoxSize(shared_ptr<Actor> actor, PxVec3& boxSize, PxVec3& center);
	/** Gets the center and the radius for the Actor that this component is attached to*/
	void getSphereSize(shared_ptr<Actor> actor, float& radius, PxVec3& center);
	/** Gets the center and the capsule description for the Actor that this component is attached to*/
	void getCapsuleGeometry(shared_ptr<Actor>actor, float &radius, float &halfHeight, RotateAxis&orientation, PxVec3& center);


    /** Pure virtual function. Clones current component (Prototype Design Pattern)
     @return shared_ptr to cloned MeshComponent Component
     */
	virtual shared_ptr<Component> clone() = 0;

    /** @defgroup serialization_functions Serialization Functions
     *  Serialization Region
     *  @{
     */
#pragma region Serialization Functions
    
	/** Creates a description for the Component*/
	virtual shared_ptr<ComponentDescription> getComponentDescription() override {return nullptr;}
    /** Deserializes a description to a Component */
    virtual void deserialize(shared_ptr<ComponentDescription> desc) override {}
    
#pragma endregion
    /** @} */ // end of serialization_functions

	
};

