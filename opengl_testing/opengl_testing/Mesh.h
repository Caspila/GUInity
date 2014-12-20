#pragma once

#include "Material.h"
#include "Module.h"
#include "StaticCounter.h"

class Mesh
#ifdef GUINITY_DEBUG
	: public StaticCounter<Mesh>
#endif
{
public:
	Mesh(const char* fileName);
	Mesh(float *points, int nPoints, float* colorPoints, float* normalPoints);
	~Mesh();

	//float *points,*colorPoints,  *normalPoints;
	vector<glm::vec3>  points, colorPoints, normalPoints;
	vector<glm::vec2> uv;

	//float*  points2, colorPoints2, normalPoints2;

	
	GLuint vbo, vao, nbo, cbo;

	int nPoints, nNormalPoints;

	void calculateBounds();
	void createBuffers();

	
	glm::vec3 boundsMin, boundsMax;
};

