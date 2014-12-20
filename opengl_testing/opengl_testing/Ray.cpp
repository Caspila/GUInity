#include "Ray.h"


Ray::Ray(glm::vec3 origin, glm::vec3 direction) {
	this->origin = origin; this->direction = direction;
}


Ray::~Ray()
{
}

Ray::Ray(Ray&& ray)
{
	this->origin = ray.origin;
	this->direction = ray.direction;
}