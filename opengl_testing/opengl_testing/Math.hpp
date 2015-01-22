#pragma once

#ifndef MATH_HPP
#define MATH_HPP

#include "Module.hpp"
#include <glm/common.hpp>
#include <glm/geometric.hpp>
#include "MathStructs.hpp"
#include <vector>

using namespace std;


//class  Math
//{
//public:
//
//	static float Deg2Radian;
//	static float Radian2Deg;
//
//	static glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest);
//	static glm::quat LookAt(glm::vec3 direction, glm::vec3 desiredUp);
//	static glm::quat LookAt(glm::vec3 direction);
//
//	static glm::vec3 projectOnPlane(glm::vec3 vector, Plane p);
//
//    static void orderVertexCCW(glm::vec3& p1, glm::vec3& p2, glm::vec3& p);
//    static bool CCW(glm::vec3& p1, glm::vec3& p2, glm::vec3& p);
//    
//	template <typename T> static int sgn(T val) {
//		return (T(0) < val) - (val < T(0));
//	}
//
//};

//float Deg2Radian = 0.0174532925f;
//float Radian2Deg = 57.2957795f;

class MeshTriangle;

#define Radian2Deg 57.2957795f
#define Deg2Radian 0.0174532925f

 glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest);
 glm::quat LookAt(glm::vec3 direction, glm::vec3 desiredUp);
 glm::quat LookAt(glm::vec3 direction);

float distanceVertexPlane(glm::vec3, Plane p);

 glm::vec3 projectOnPlane(glm::vec3 vector, Plane p);

bool isPlaneFacingPoint(const Plane& p,const glm::vec3& vector);

//void orderVertexCCW(glm::vec3& p1, int& i1, glm::vec3& p2, int& i2, glm::vec3& p3, int& i3);
// void orderVertexCCW(glm::vec3& p1, glm::vec3& p2, glm::vec3& p);
// bool CCW(glm::vec3& p1, glm::vec3& p2, glm::vec3& p);
bool CCW(glm::vec3& p1, glm::vec3& p2, glm::vec3& p,const glm::vec3& POV);

void orderVertexCCW(glm::vec3& p1, glm::vec3& p2, glm::vec3& p3,glm::vec3& POV);
void orderVertexCCW(glm::vec3& p1, int& i1, glm::vec3& p2, int& i2, glm::vec3& p3);

glm::mat4 getPOVMat(glm::vec3& p1, glm::vec3& p2, glm::vec3& p3, const glm::vec3& POV);

//shared_ptr<MeshTriangle> createMeshTriangle(vector<glm::vec3> vertices, int i1, int i2, int i3);
shared_ptr<MeshTriangle> createMeshTriangle(vector<glm::vec3> vertices, int i1, int i2, int i3, glm::vec3 normalRef);

template <typename T> static int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

void convexHull(vector<glm::vec3>& vertices, vector<int>& usedIndex, vector<int>& triangles);

#endif