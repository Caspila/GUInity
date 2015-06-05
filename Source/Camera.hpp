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

/** Camera Component. This component simulates a camera in a 3D environment. It's the point of view used for rendering the Actors of the Game */
class Camera : public Component, public Subject<Camera>
#ifdef GUINITY_DEBUG
	, public StaticCounter<Camera>
#endif
{
private:
	/** Current Model View Projection Matrix */
	glm::mat4 MVPMatrix;
	/** Projection Matrix */
	glm::mat4 projection;
	/** View Matrix */
	glm::mat4 view;

	/** Near Clip Plane */
	float nearClipPlane;
	/** Far Clip Plane */
	float farClipPlane;
	/** Field of Vision (degrees)*/
	float fov;
	/** Screen Ratio */
	float ratio;


public:
	/** Default Constructor */
	Camera();
	/** Constructor with custom parameters near clip plane, far clip plane, field of vision and screen ratio. */
	Camera(float nearClipPlane, float farClipPlane, float fov, float ratio);
	/** Default Destructor. Virtual because inherits Component */
	virtual ~Camera();

	/** Computes the current Model View Matrix and puts it into MVPMatrix */
	void computeModelViewMatrix();
	/** Returns Model Matrix without the scale factor */
	glm::mat4 getModelMatrix();

	/** MVPMatrix Getter*/
	glm::mat4 getMVPMatrix();
	/** projection Matrix Getter*/
	glm::mat4 getProjectionMatrix();
	/** view Matrix Getter*/
	glm::mat4 getViewMatrix();
	/** near clip Getter*/
	float getNearClip();
	/** far clip Getter*/
	float getFarClip();
	/** fov Getter*/
	float getFOV();
	/** screen ratio Getter*/
	float getScreenRatio();

	/** Transforms a screen point to a world point. Commonly used for transforming mouse position into world points */
	glm::vec3 screenPointToWorld(glm::vec2 pos);
	/** Transforms a screen point to Ray. Commonly used for transforming mouse position into a Ray */
	Ray screenPointToRay(glm::vec2 pos);
	/** Transforms a screen point to Ray. Commonly used for transforming mouse position into a Ray */
	Ray screenPointToRay2(glm::vec2 pos);

	/** Component init override. Notifies that a new camera has been created */
	virtual void init() override;


	virtual void destroy() override;
	
    /** Component awake override. Computes MVPMatrix */
	virtual void awake() override;
	/** Component tick override. Computes MVPMatrix */
	virtual void tick(float deltaSecods) override;
   

	/** Prototype design pattern*/
	virtual shared_ptr<Component> clone() override;
	
	/** Serialization region*/
	/** Get a description for the current component*/
    virtual shared_ptr<ComponentDescription> getComponentDescription();
	/** Deserialize a component description into this collider */
    virtual void deserialize(shared_ptr<ComponentDescription> desc);

};

