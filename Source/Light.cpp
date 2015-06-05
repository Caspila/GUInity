#include "Light.hpp"
#include "Actor.hpp"

/** Default Constructor. White Light */
Light::Light() : Light(glm::vec3(1,1,1)) {}

/** Default Constructor. Colored Light */
Light::Light(glm::vec3 c) : color {c}
{
	   
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

/** Default Destructor */
Light::~Light()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "Light destroyed (" << nCount << " remaining)" << endl;
#endif
	
}


/** color setter*/
glm::vec3 Light::getColor()
{
	return color;
}
/** color setter*/
void Light::setColor(glm::vec3 color)
{
	this->color = color;
}

/** Component init override. Notifies that a new light has been created*/
void Light::init()
{
	Light::notify(ComponentEventType::NewLight, shared_from_this(), getActor()->getEditorFlag());
}

/** Prototype design pattern*/
shared_ptr<Component> Light::clone()
{
    shared_ptr<Light> compClone = make_shared<Light>(getColor());
    return compClone;
}

/** Get a description for the current component*/
shared_ptr<ComponentDescription> Light::getComponentDescription()
{
    return make_shared<LightDescription>(color);
}

/** Deserialize a description into this instance*/
void Light::deserialize(shared_ptr<ComponentDescription> desc)
{
    shared_ptr<LightDescription> lightDesc = dynamic_pointer_cast<LightDescription>(desc);
    
    color = lightDesc->color;
}