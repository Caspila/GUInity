//
//  MathStructs.h
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-14.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

//#include "Math.cpp"


#ifndef opengl_testing_mag_MathStructs_h
#define opengl_testing_mag_MathStructs_h

#include <glm/glm.hpp>

/** Plane, a point and a normal */
struct Plane
{
	/** Point */
	glm::vec3 point;
	/** Normal */
	glm::vec3 normal;
    
	/** Default Constructor */
    Plane() {}
	/** Default Destructor */
	~Plane(){};
    
	/** Constructor with point and normal */
	Plane(glm::vec3 point, glm::vec3 normal);

	/** Constructor from 3 points. Assumes points are given in CCW */
	Plane(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
    
	/** Constructor from 3 points. Uses Point of View to order points CCW */
    Plane(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3,glm::vec3 POV);
    
	
};


#endif
