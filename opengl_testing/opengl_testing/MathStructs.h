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

struct Plane
{
	glm::vec3 point;
	glm::vec3 normal;
    
    Plane() {}
    
	Plane(glm::vec3 point, glm::vec3 normal);

	Plane(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
    
    Plane(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3,glm::vec3 POV);
    
	~Plane(){};
};


#endif
