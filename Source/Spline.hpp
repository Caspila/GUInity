//  ANIMATION IS CURRENTLY UNDER DEVELOPMENT
//  ANIMATION IS CURRENTLY UNDER DEVELOPMENT
//  ANIMATION IS CURRENTLY UNDER DEVELOPMENT
//
//  Spline.h
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-06-07.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __GUInity_MacOS__Spline__
#define __GUInity_MacOS__Spline__

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

class Spline
{
private:
    std::vector<glm::dvec3> points;
    
    double factorial(int n);
    static double factorialLookup[33];
    
    double bernstein(int n, int i, double t);
    
    double Ni(int n, int i);
    
public:
    glm::vec3 evaluate3D(float t);
    glm::vec2 evaluate2D(float t);
    double evaluate(float t);
};

#endif /* defined(__GUInity_MacOS__Spline__) */
