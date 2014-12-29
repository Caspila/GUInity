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


Light::~Light()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "Light destroyed (" << nCount << " remaining)" << endl;
#endif
	
}


void Light::init()
{
	Light::notify(ComponentEventType::NewLight, shared_from_this(), getActor()->editorFlag);
}