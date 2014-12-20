#pragma once

#include "Transform.h"

class Light
#ifdef GUINITY_DEBUG
	: public StaticCounter<Light>
#endif
{
public:
	Light(glm::vec3 position, glm::vec3 color);
	~Light();

	Transform transform;
	glm::vec3 color;

};

