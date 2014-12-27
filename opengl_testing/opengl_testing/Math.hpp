#pragma once

#include <glm/common.hpp>
#include "Module.hpp"

using namespace std;

class  Math
{
public:

	static float Deg2Radian;
	static float Radian2Deg;

	static glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest);
	static glm::quat LookAt(glm::vec3 direction, glm::vec3 desiredUp);
	static glm::quat LookAt(glm::vec3 direction);

};

