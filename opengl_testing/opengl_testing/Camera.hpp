#pragma once

#include "Module.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Ray.hpp"
#include "Component.hpp"
#include "Subject.hpp"

class Transform;

using namespace std;


class Camera : public Component, public Subject<Camera>, public enable_shared_from_this<Camera>
#ifdef GUINITY_DEBUG
	, public StaticCounter<Camera>
#endif
{
public:
	Camera();
	Camera(float nearClipPlane, float farClipPlane, float fov, float ratio);
	~Camera();

	//shared_ptr<Transform> transform;

	void computeModelViewMatrix();

	glm::mat4 MVPMatrix;

	float nearClipPlane, farClipPlane;
	float fov;
	float ratio;

	glm::vec3 screenPointToWorld(glm::vec2 pos);
	Ray screenPointToRay(glm::vec2 pos);
	Ray screenPointToRay2(glm::vec2 pos);
	glm::mat4 getModelMatrix();

	glm::mat4 projection;
	glm::mat4 view;

	static int nCount;

	virtual void init() override;
	virtual void awake() override;
	virtual void tick(float deltaSecods) override;

private:

};

