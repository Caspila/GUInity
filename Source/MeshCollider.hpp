#pragma once
#include "Collider.hpp"

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

	/** Prototype design pattern*/
	virtual shared_ptr<Component> clone() override;

	/** Serialization region*/
	/** Get a description for the current component*/
	virtual shared_ptr<ComponentDescription> getComponentDescription();
	/** Deserialize a component description into this collider */
	virtual void deserialize(shared_ptr<ComponentDescription> desc);
    
};

