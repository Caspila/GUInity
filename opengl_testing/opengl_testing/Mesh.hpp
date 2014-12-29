#pragma once

//#include "Material.h"
#include "Module.hpp"
//#include "StaticCounter.h"
#include <vector>
#include <glm/common.hpp>

class Mesh
#ifdef GUINITY_DEBUG
	: public StaticCounter<Mesh>
#endif
{
public:
	Mesh(const char* fileName);
	Mesh(float *points, int nPoints, float* colorPoints, float* normalPoints);
	Mesh(float* indices, unsigned int *triangles, int nPoints, int nTriangles, float* normalPoints);
	~Mesh();

	//float *points,*colorPoints,  *normalPoints;
	vector<glm::vec3> indices;
	vector<unsigned int> triangles;

	vector<glm::vec3>  points, colorPoints, normalPoints;
	vector<glm::vec2> uv;

	//float*  points2, colorPoints2, normalPoints2;

	
	GLuint vbo, vao, nbo, cbo, ibo;
	

	int nPoints, nNormalPoints;

	void calculateBounds();
	void calculateBounds2();
	void createBuffers();
	void createBuffers2();

	
	glm::vec3 boundsMin, boundsMax;
};

