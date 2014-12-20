#pragma once

#include "Module.h"
#include "Vector3.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include "Math.h"
#include "Ray.h"
#include "Transform.h"

using namespace std;

class Camera
{
public:
	Camera(float nearClipPlane, float farClipPlane, float fov, float ratio);
	~Camera();

	shared_ptr<Transform> transform;

	void computeModelViewMatrix();

	glm::mat4 MVPMatrix;

	float nearClipPlane, farClipPlane;
	float fov;
	float ratio;

	Ray screenPointToRay(glm::vec2 pos);
	Ray screenPointToRay2(glm::vec2 pos);
	glm::mat4 getModelMatrix();

	glm::mat4 projection;
	glm::mat4 view;
private:

};

