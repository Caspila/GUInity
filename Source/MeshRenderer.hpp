#pragma once

#include "Module.hpp"
#include "Component.hpp"
#include "Subject.hpp"

//#include "Mesh.h"
//#include "Material.h"

class Mesh;
class Material;
class MeshFilter;
class MeshComponent;

class MeshRenderer : public Component, public Subject<MeshRenderer>
#ifdef GUINITY_DEBUG
, public StaticCounter<MeshRenderer>
#endif
{
private:
    /** Reference to the mesh that this renderer renders */
	weak_ptr<MeshComponent> meshComponent;
    /** Reference to the material that will be used to render */
	shared_ptr<Material> material;
    
public:
    /** Default Constructor */
	MeshRenderer();
    /** Default Destructor. Virtual cause it's child class */
    virtual ~MeshRenderer();
    
    /** material setter */
    void setMaterial(shared_ptr<Material> material);
    /** material getter */
    const shared_ptr<Material> getMaterial()  const;
	
    /** meshComponent setter */
    void setMeshComponent(shared_ptr<MeshComponent> mesh);
    /** meshComponent getter */
    shared_ptr<MeshComponent> getMeshComponent() const;
	
    /** Component init override. Tries to get a MeshComponent from the owner Actor and notifies that a new MeshRenderer has been created */
    virtual void init() override;
    /** Component destroy. Notifies this MeshRenderer has been destroyed */
    virtual void destroy() override;
    
    
    /** Clones current component (Prototype Design Pattern)
     @return shared_ptr to cloned MeshRenderer Component
     */
    virtual shared_ptr<Component> clone() override;
    
    /** @defgroup serialization_functions Serialization Functions
     *  Serialization Region
     *  @{
     */
#pragma region Serialization Functions
    
	/** Creates a description for the Component*/
	virtual shared_ptr<ComponentDescription> getComponentDescription() override;
    /** Deserializes a description to a Component */
    virtual void deserialize(shared_ptr<ComponentDescription> desc) override;
    
#pragma endregion
    /** @} */ // end of serialization_functions
};

