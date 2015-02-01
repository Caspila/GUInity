#include "Camera.hpp"
#include "print.hpp"
#include "Math.hpp"
#include "Transform.hpp"
#include "Actor.hpp"

int Camera::nCount = 0;

Camera::Camera() : Camera(0.3f, 100.0f, 45.0f, 4.0f / 3.0f){}


Camera::Camera(float nearClipPlane, float farClipPlane, float fov, float ratio)
{
	this->nearClipPlane = nearClipPlane;
	this->farClipPlane = farClipPlane;
	this->fov = fov;
	this->ratio = ratio;

	//transform = getActor()->

	//transform = make_shared<Transform>();
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}


Camera::~Camera()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "Camera destroyed (" << nCount << " remaining)" << endl;
#endif
	
}

void Camera::computeModelViewMatrix()
{
	//glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	projection = glm::perspective(fov,ratio,nearClipPlane,farClipPlane);

	//glm::vec3 up(0, 1, 0);
	//
	//glm::mat4 look = glm::lookAt(getActor()->transform->position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//glm::mat4 look2 = getActor()->transform->getPosRotMatrix();
	//glm::mat4 look3 = getActor()->transform->getPosRotMatrix();
	//
	view = glm::lookAt(getActor()->transform->position, getActor()->transform->position+getActor()->transform->getForward(), getActor()->transform->getUp());
	//view = getActor()->transform->getPosRotMatrix();
	//view = (glm::mat4)getActor()->transform->getRotationQuat() *  glm::translate(getActor()->transform->position);
	//view = glm::translate(getActor()->transform->position) * (glm::mat4)Math::LookAt(getActor()->transform->getForward(), getActor()->transform->getUp());
	
	// Right one
	//view = glm::lookAt(getActor()->transform->position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	
	MVPMatrix = projection * view;
}

glm::mat4 Camera::getModelMatrix()
{
	return getActor()->transform->getPosRotMatrix();
	//return glm::translate(position)  * glm::rotate(rotation.x * Math::Deg2Radian, glm::vec3(1, 0, 0)) *
	//	glm::rotate(rotation.y * Math::Deg2Radian, glm::vec3(0, 1, 0)) *
	//	glm::rotate(rotation.z * Math::Deg2Radian, glm::vec3(0, 0, 1));
}


glm::vec3 Camera::screenPointToWorld(glm::vec2 pos)
{
	float x = (2.0f * pos.x) / 640 - 1.0f;
	float y = 1.0f - (2.0f * pos.y) / 480;
	float z = 1.0f;
	glm::vec3 ray_nds(x, y, z);

	//cout << "x: " << x << "  y: " << y << endl;

	glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0, 1.0);
	glm::vec4 ray_eye = glm::inverse(projection) * ray_clip;

	ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);

	glm::vec4 ray_w = (glm::inverse(view) * ray_eye);

	glm::vec3 ray_wor(ray_w.x, ray_w.y, ray_w.z);

	return ray_wor;
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

	glm::vec3 ray_origin = getActor()->transform->position;// +ray_wor*nearClipPlane;

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

void Camera::init()
{
	Camera::notify(ComponentEventType::NewCamera, shared_from_this(), getActor()->getEditorFlag());
}

void Camera::awake()
{
	computeModelViewMatrix();
}
void Camera::tick(float deltaSecods)
{
	computeModelViewMatrix();
}

shared_ptr<ComponentDescription> Camera::getComponentDescription()
{
    
    float nearClipPlane, farClipPlane;
	float fov;
	float ratio;

    return make_shared<CameraDescription>(nearClipPlane,farClipPlane,fov,ratio);
    
}


 void Camera::deserialize(shared_ptr<ComponentDescription> desc)
{
    
    shared_ptr< CameraDescription> cameraDesc = dynamic_pointer_cast<CameraDescription>(desc);
    
    nearClipPlane = cameraDesc->nearClipPlane;
    farClipPlane = cameraDesc->farClipPlane;
    ratio = cameraDesc->ratio;
    fov = cameraDesc->fov;
    
}
