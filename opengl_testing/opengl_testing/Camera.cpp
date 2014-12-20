#include "Camera.h"
#include "print.h"

Camera::Camera(float nearClipPlane, float farClipPlane, float fov, float ratio)
{
	this->nearClipPlane = nearClipPlane;
	this->farClipPlane = farClipPlane;
	this->fov = fov;
	this->ratio = ratio;

	transform = make_shared<Transform>();
}


Camera::~Camera()
{
}

void Camera::computeModelViewMatrix()
{
	//glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	projection = glm::perspective(fov,ratio,nearClipPlane,farClipPlane);

	glm::vec3 up(0, 1, 0);

	//glm::mat4 view = glm::lookAt(position, rotation, up);
	
	//float x = glm::cos(rotation.x)*glm::cos(rotation.y);
	//float y = glm::sin(rotation.x)*glm::cos(rotation.y);
	//float z = glm::sin(rotation.y);

	view = glm::lookAt(transform->position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//view = glm::lookAt(position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	// view = glm::translate(position) * glm::rotate(rotation.x * Math::Deg2Radian, glm::vec3(1, 0, 0)) *
	//	glm::rotate(rotation.y * Math::Deg2Radian, glm::vec3(0, 1, 0)) *
	//	glm::rotate(rotation.z * Math::Deg2Radian, glm::vec3(0, 0, 1));

	//glm::mat4 model = glm::mat4(1.0f);

	//VPMatrix = projection * view;
	MVPMatrix = projection * view;
}

glm::mat4 Camera::getModelMatrix()
{
	return transform->getPosRotMatrix();
	//return glm::translate(position)  * glm::rotate(rotation.x * Math::Deg2Radian, glm::vec3(1, 0, 0)) *
	//	glm::rotate(rotation.y * Math::Deg2Radian, glm::vec3(0, 1, 0)) *
	//	glm::rotate(rotation.z * Math::Deg2Radian, glm::vec3(0, 0, 1));
}

Ray Camera::screenPointToRay(glm::vec2 pos)
{
	float x = (2.0f * pos.x) / 640 - 1.0f;
	float y = 1.0f - (2.0f * pos.y) / 480;
	float z = 1.0f;
	glm::vec3 ray_nds(x, y, z);

	//cout << "x: " << x << "  y: " << y << endl;

	glm::vec4 ray_clip = glm::vec4(ray_nds.x,ray_nds.y, -1.0, 1.0);
	glm::vec4 ray_eye = glm::inverse(projection) * ray_clip;

	//cout << "ray_eye:" << ray_eye << endl;

	ray_eye = glm::vec4(ray_eye.x,ray_eye.y, -1.0, 0.0);

	glm::vec4 ray_w = (glm::inverse(view) * ray_eye);

	glm::vec3 ray_wor(ray_w.x, ray_w.y, ray_w.z);
	// don't forget to normalise the vector at some point
	ray_wor = glm::normalize(ray_wor);

	//cout << "ray_wor:" << ray_wor << endl;

	glm::vec3 ray_origin = transform->position;// +ray_wor*nearClipPlane;

	return Ray(ray_origin, ray_wor);
}

Ray Camera::screenPointToRay2(glm::vec2 pos)
{
	glm::vec2 normalizedPos;
	normalizedPos.x = (2 * (pos.x - 640) / 640) - 1;
	normalizedPos.y = -((2 * (pos.y - 480) / 480) - 1);

	glm::mat4 U = glm::inverse(projection * getModelMatrix());

	glm::vec4 lNear(normalizedPos.x, normalizedPos.y, 0, 1);
	glm::vec4 lFar(normalizedPos.x, normalizedPos.y, 1, 1);

	glm::vec4 R_near = U *  lNear;
	glm::vec4 R_far = U *  lFar;

	glm::vec3 R3_near(R_near.x / R_near.w,
		R_near.y / R_near.w,
		R_near.z / R_near.w);
	glm::vec3 R3_far(R_far.x / R_far.w,
		R_far.y / R_far.w,
		R_far.z / R_far.w);

	return Ray(R3_near,normalize(R3_far - R3_near));
}