#include "Light.h"


Light::Light(glm::vec3 position, glm::vec3 color)
{
	transform.setPosition(position);
	this->color = color;
}


Light::~Light()
{
	cout << "Light destroyed" << endl;
}
