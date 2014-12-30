#pragma once

//#include "Material.h"
#include "Module.hpp"
//#include "StaticCounter.h"
#include <vector>
#include <glm/common.hpp>

struct MeshVertex
{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;

	MeshVertex(glm::vec3 p, glm::vec2 u, glm::vec3 n) : position(p), uv(u), normal(n) {}
	MeshVertex(){}
	
};

class Mesh
#ifdef GUINITY_DEBUG
	: public StaticCounter<Mesh>
#endif
{


public:
	Mesh();

	//Mesh(const char* fileName);
	//Mesh(float *points, int nPoints, float* colorPoints, float* normalPoints);
	//Mesh(float* indices, unsigned int *triangles, float* normalPoints, int nPoints, int nTriangles);
	Mesh(float* indices, float* normalPoints, float* uv, unsigned int *triangles, int nPoints, int nTriangles);
	~Mesh();

	//float *points,*colorPoints,  *normalPoints;
	//vector<glm::vec3> indices;
	vector<unsigned short> triangles;

	//vector<glm::vec3>  points, colorPoints, normalPoints;
	//vector<glm::vec2> uv;

	vector<MeshVertex> meshVertices;

	void scale(float f);

	void addVertex(glm::vec3 position, glm::vec2 uv, glm::vec3 normal);
	//bool closeEnough(MeshVertex& v, glm::vec3& point, glm::vec2& uv, glm::vec3& normal);
	//int vertexExists(glm::vec3& vec3, glm::vec2& uv, glm::vec3& normal);
	//unsigned short getVertexIndex(glm::vec3& vec3, glm::vec2& uv, glm::vec3& normal);
	//MeshVertex getVertex(glm::vec3& vec3, glm::vec2& uv, glm::vec3& normal);
	//void addTriangle(glm::vec3 position, glm::vec2 uv, glm::vec3 normal,
	//					   glm::vec3 position2, glm::vec2 uv2, glm::vec3 normal2,
	//					   glm::vec3 position3, glm::vec2 uv3, glm::vec3 normal3);
	//void addTriangle(glm::vec3 position, glm::vec2 uv, glm::vec3 normal);
	void addTriangle(int vertexIndex);

	//GLuint vbo, vao, nbo, cbo, ibo;
	// Vertex array
	GLuint vao;
	// Triangles array
	GLuint ibo;
	// Vertex data array
	GLuint mvbo;

	int nPoints, nNormalPoints;

	//void calculateBounds();
	//void createBuffers();
	//
	//void calculateBounds2();
	//void createBuffers2();

	void createBuffers3();
	void calculateBounds3();
	
	glm::vec3 boundsMin, boundsMax, avgCenter;
};

