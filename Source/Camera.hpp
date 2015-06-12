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

/** Camera Component. This component simulates a camera in a 3D environment. It's the point of view used for rendering the Actors of the World */
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
	float getNearClip() const;
	/** far clip Getter*/
	float getFarClip() const;
	/** fov Getter*/
	float getFOV() const;
	/** screen ratio Getter*/
	float getScreenRatio() const;

    /** near clip Setter*/
	void setNearClip(float nearClipPlane) ;
	/** far clip Setter*/
	void setFarClip(float farClipPlane) ;
	/** fov Setter*/
	void setFOV(float fov) ;
	/** screen ratio Setter*/
	void setScreenRatio(float ratio) ;
    
    
	/** Transforms a screen point to a world point. Commonly used for transforming mouse position into world points */
	glm::vec3 screenPointToWorld(glm::vec2 pos);
	/** Transforms a screen point to Ray. Commonly used for transforming mouse position into a Ray */
	Ray screenPointToRay(glm::vec2 pos);
	/** Transforms a screen point to Ray. Commonly used for transforming mouse position into a Ray */
	Ray screenPointToRay2(glm::vec2 pos);

	/** Component init override. Notifies that a new camera has been created */
	virtual void init() override;
    /** Component destroy override. Notifies that the camera has been destroyed */
	virtual void destroy() override;
	
    /** Component awake override. Computes MVPMatrix */
	virtual void awake() override;
	/** Component tick override. Computes MVPMatrix */
	virtual void tick(float deltaSecods) override;
   
    
    

    /** Clones current component (Prototype Design Pattern)
     @return shared_ptr to cloned Camera Component
     */
	virtual shared_ptr<Component> clone() override;
	
    /** @defgroup serialization_functions Serialization Functions
     *  Serialization Region
     *  @{
     */
#pragma region Serialization Functions
    
	/** Creates a description for the Component*/
	virtual shared_ptr<ComponentDescription> getComponentDescription() override;
    /** Deserializes a description to a Component */
    virtual void deserialize(shared_ptr<ComponentDescription> desc) override;
    
#pragma endregion
    /** @} */ // end of serialization_functions

};

