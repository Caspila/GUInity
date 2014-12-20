#pragma once

#include "Transform.h"

class Light
{
public:
	Light(glm::vec3 position, glm::vec3 color);
	~Light();

	Transform transform;
	glm::vec3 color;


};

