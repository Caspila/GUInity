#pragma once
#include "Collider.hpp"

/** BoxCollider uses a Mesh as the volume collider. Can either be real physics simulated or trigger only. */
class MeshCollider : public Collider
#ifdef GUINITY_DEBUG
	, public StaticCounter<MeshCollider>
#endif
{
public:
	/** Default Constructor*/
	MeshCollider();
	/** Default Destructor. Virtual because inherits from Collider*/
	virtual ~MeshCollider();

	/** Init component override. Create a new Mesh Shape in the PhysX scene. */
	virtual void init();

	/** Component tick override. Updates the scale of the Mesh Shape in the PhysX scene. */
	virtual void tick(float deltaSeconds) override;

    /** Clones current component (Prototype Design Pattern)
     @return shared_ptr to cloned MeshCollider Component
     */
	virtual shared_ptr<Component> clone() override;

    /** @defgroup serialization_functions Serialization Functions
     *  Serialization Region
     *  @{
     */
#pragma region Serialization Functions
    
	/** Creates a description for the Component*/
	virtual shared_ptr<ComponentDescription> getComponentDescription() override {return nullptr;}
    /** Deserializes a description to a Component */
    virtual void deserialize(shared_ptr<ComponentDescription> desc) override {};
    
#pragma endregion
    /** @} */ // end of serialization_functions
    
};

