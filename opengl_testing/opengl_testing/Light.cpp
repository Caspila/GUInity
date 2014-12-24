#include "Light.hpp"

Light::Light(glm::vec3 position, glm::vec3 color)
{
	transform.setPosition(position);
	this->color = color;

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
