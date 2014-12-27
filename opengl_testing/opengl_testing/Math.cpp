#include "Math.hpp"
#include <glm/common.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/common.hpp>


float Math::Deg2Radian = 0.0174532925f;
float Math::Radian2Deg = 57.2957795f;


// Code from http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/

glm::quat Math::RotationBetweenVectors(glm::vec3 start, glm::vec3 dest){
	start = normalize(start);
	dest = normalize(dest);

	float cosTheta = dot(start, dest);
	glm::vec3 rotationAxis;


	if (cosTheta < -1 + 0.001f){
		// special case when vectors in opposite directions:
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
		if (glm::length2(rotationAxis) < 0.01) // bad luck, they were parallel, try again!
			rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);

		rotationAxis = normalize(rotationAxis);
		return glm::angleAxis(180.0f, rotationAxis);
	}

	rotationAxis = cross(start, dest);

	float s = sqrt((1 + cosTheta) * 2);
	float invs = 1 / s;

	return glm::quat(
		s * 0.5f,
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
		);

}

glm::quat Math::LookAt(glm::vec3 direction){
	// Find the rotation between the front of the object (that we assume towards +Z, 
	// but this depends on your model) and the desired direction 
	return RotationBetweenVectors(glm::vec3(0.0f, 0.0f, 1.0f), direction);
}

glm::quat Math::LookAt(glm::vec3 direction, glm::vec3 desiredUp){
	// Find the rotation between the front of the object (that we assume towards +Z, 
	// but this depends on your model) and the desired direction 
	glm::quat rot1 = RotationBetweenVectors(glm::vec3(0.0f, 0.0f, 1.0f), direction);

	// Recompute desiredUp so that it's perpendicular to the direction
	// You can skip that part if you really want to force desiredUp
	glm::vec3 right = glm::cross(direction, desiredUp);
	desiredUp = glm::cross(right, direction);

	// Because of the 1rst rotation, the up is probably completely screwed up. 
	// Find the rotation between the "up" of the rotated object, and the desired up
	glm::vec3 newUp = rot1 * glm::vec3(0.0f, 1.0f, 0.0f);
	glm::quat rot2 = RotationBetweenVectors(newUp, desiredUp);

	glm::quat targetOrientation = rot2 * rot1; // remember, in reverse orde

	return targetOrientation;
}