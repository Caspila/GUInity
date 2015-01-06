#pragma once

#include "Module.hpp"
#include "Component.hpp"
#include "Subject.hpp"
//#include "Mesh.h"
//#include "Material.h"

class Mesh;
class Material;
class MeshFilter;

class MeshRenderer : public Component, public Subject<MeshRenderer>
#ifdef GUINITY_DEBUG
	, public StaticCounter<MeshRenderer>
#endif
{
public:
	MeshRenderer();//shared_ptr<Mesh> mesh, shared_ptr<Material> m);
	~MeshRenderer();

	weak_ptr<MeshFilter> meshFilter;
	shared_ptr<Material> material;
    
    
    void setMaterial(shared_ptr<Material> material);
	virtual void init() override;

    
    virtual shared_ptr<ComponentDescription> getComponentDescription() override;
    
    virtual shared_ptr<Component> clone() override{ shared_ptr<MeshRenderer> compClone = make_shared<MeshRenderer>(); return compClone;} ;
    
        void deserialize(shared_ptr<ComponentDescription> desc) override;    
};

