#include "Light.hpp"
#include "Actor.hpp"

Light::Light()
{
	//transform.setPosition(position);
	//this->color = color;

	color = glm::vec3(1, 1, 1);

#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

Light::Light(glm::vec3 c) : color {c}
{
	   
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}


Light::~Light()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "Light destroyed (" << nCount << " remaining)" << endl;
#endif
	
}


void Light::init()
{
	Light::notify(ComponentEventType::NewLight, shared_from_this(), getActor()->getEditorFlag());
}


shared_ptr<ComponentDescription> Light::getComponentDescription()
{
    return make_shared<LightDescription>(color);
}

void Light::deserialize(shared_ptr<ComponentDescription> desc)
{
    shared_ptr<LightDescription> lightDesc = dynamic_pointer_cast<LightDescription>(desc);
    
    color = lightDesc->color;
}