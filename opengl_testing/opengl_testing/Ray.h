#pragma once

#include <glm\common.hpp>

class Ray
{
public:
	Ray(glm::vec3 origin, glm::vec3 direction);
	~Ray();
	//Move constructor
	Ray(Ray&& ray);

	glm::vec3 origin;
	glm::vec3 direction;

};

