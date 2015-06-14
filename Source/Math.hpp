#pragma once

#ifndef MATH_HPP
#define MATH_HPP

#include "Module.hpp"
#include <glm/common.hpp>
#include <glm/geometric.hpp>
#include "MathStructs.hpp"
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;


struct MeshTriangle;

#define Radian2Deg 57.2957795f
#define Deg2Radian 0.0174532925f

/** Get Rotation between two vectors */
 glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest);
 /** Get Quaternion from forward to direction and Up vector */
 glm::quat LookAt(glm::vec3 direction, glm::vec3 desiredUp);
 /** Get Quaternion from forward to direction */
 glm::quat LookAt(glm::vec3 direction);

 /** Returns the distance between a vec3 and a Plane */
float distanceVertexPlane(glm::vec3, Plane p);
/** Returns the projection of a vec3 in a Plane */
 glm::vec3 projectOnPlane(glm::vec3 vector, Plane p);

 /** CONVEX HULL SECTION */
 /** CONVEX HULL IS NOT WORKING CURRENTLY */
 /** CONVEX HULL IMPLEMENTATION WAS DROPPED BECAUSE PHYSX CAN CALCULATE IT */

 /** Checks if a vec3 is on the right side (normal facing side) of a Plane */
bool isPlaneFacingPoint(const Plane& p,const glm::vec3& vector);
/** Checks if 3 points are ordered counter clockwise based on a vec3 point of view */
bool CCW(glm::vec3& p1, glm::vec3& p2, glm::vec3& p,const glm::vec3& POV);
/** Order 3 points counter clockwise based on a vec3 point of view */
void orderVertexCCW(glm::vec3& p1, glm::vec3& p2, glm::vec3& p3,glm::vec3& POV);
/** Order 3 points counter clockwise based on a vec3 point of view. i1,i2 and i3 are used if the vertex
are stored in an array or something similar*/
void orderVertexCCW(glm::vec3& p1, int& i1, glm::vec3& p2, int& i2, glm::vec3& p3);
/** Get a matrix4x4 that represents the point of view and 3 points */
glm::mat4 getPOVMat(glm::vec3& p1, glm::vec3& p2, glm::vec3& p3, const glm::vec3& POV);
/** Get a matrix4x4 that represents the point of view and 3 points */
shared_ptr<MeshTriangle> createMeshTriangle(vector<glm::vec3> vertices, int i1, int i2, int i3, glm::vec3 normalRef);

template <typename T> static int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

template <class T> const T& min (const T& a, const T& b) {
    return !(b<a)?a:b;     // or: return !comp(b,a)?a:b; for version (2)
}

#endif