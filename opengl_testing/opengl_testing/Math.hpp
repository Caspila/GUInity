#pragma once

#include "Module.hpp"
#include <glm/common.hpp>
#include <glm/geometric.hpp>


using namespace std;


struct Plane
{
	glm::vec3 point;
	glm::vec3 normal;

	Plane(glm::vec3 point, glm::vec3 normal)
	{
		this->point = point;
		this->normal = glm::normalize(normal);
	}

	Plane(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3)
	{
		glm::vec3 a = point1 - point2;
		glm::vec3 b = point1 - point3;

		this->point = point1;
		this->normal = glm::normalize(glm::cross(a, b));
	}

	~Plane(){};
};

class  Math
{
public:

	static float Deg2Radian;
	static float Radian2Deg;

	static glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest);
	static glm::quat LookAt(glm::vec3 direction, glm::vec3 desiredUp);
	static glm::quat LookAt(glm::vec3 direction);

	static glm::vec3 projectOnPlane(glm::vec3 vector, Plane p);

	template <typename T> static int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}

};


