//
//  MathStructs.cpp
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-14.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "Math.hpp"

Plane::Plane(glm::vec3 point, glm::vec3 normal)
{
    this->point = point;
    this->normal = glm::normalize(normal);
}

Plane::Plane(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3)
{
    //orderVertexCCW(point1,point2,point3);
    
    glm::vec3 a = point2 - point1;
    glm::vec3 b = point3 - point1;

    this->point = point1;
    this->normal = glm::normalize(glm::cross(a, b));

}

Plane::Plane(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 POV)
{
    orderVertexCCW(point1,point2,point3,POV);
    
    glm::vec3 a = point2 - point1;
    glm::vec3 b = point3 - point1;
    //glm::vec3 a = point1 - point2;
    //glm::vec3 b = point1 - point3;
    
    this->point = point1;
    this->normal = glm::normalize(glm::cross(a, b));
    //this->normal = glm::normalize(glm::cross(b, a));
}