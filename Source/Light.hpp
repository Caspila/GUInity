#pragma once

#include "Transform.hpp"
#include "Subject.hpp"
#include "Component.hpp"

class Light : public Component, public Subject<Light>
#ifdef GUINITY_DEBUG
	, public StaticCounter<Light>
#endif
{
public:
	Light(glm::vec3 color);
    Light();
	//Light(glm::vec3 color);
	~Light();

	//Transform transform;
	glm::vec3 color;

	virtual void init() override;
    
    
    virtual shared_ptr<ComponentDescription> getComponentDescription();
    virtual shared_ptr<Component> clone() { shared_ptr<Light> compClone = make_shared<Light>();return compClone;};
    
    virtual void deserialize(shared_ptr<ComponentDescription> desc);

};

