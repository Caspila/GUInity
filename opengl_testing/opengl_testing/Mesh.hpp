#pragma once

#ifndef MESH_HPP
#define MESH_HPP

//#include "Material.h"
#include "Module.hpp"
//#include "StaticCounter.h"
#include <vector>
#include <glm/common.hpp>
#include "Asset.hpp"

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>

struct MeshVertex
{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;

	MeshVertex(glm::vec3 p, glm::vec2 u, glm::vec3 n) : position(p), uv(u), normal(n) {}
	MeshVertex(){}
	
};

class Mesh : public Asset
#ifdef GUINITY_DEBUG
	, public StaticCounter<Mesh>
#endif
{


public:
	Mesh();
	Mesh(float* indices, float* normalPoints, float* uv, unsigned int *triangles, int nPoints, int nTriangles);
	
    virtual ~Mesh();
    
	vector<unsigned short> triangles;

	vector<MeshVertex> meshVertices;

	void setScaleFactor(float f);

	void addVertex(glm::vec3 position, glm::vec2 uv, glm::vec3 normal);
	void addTriangle(int vertexIndex);

	// Vertex array
	GLuint vao;
	// Triangles array
	GLuint ibo;
	// Vertex data array
	GLuint mvbo;

	//int nPoints, nNormalPoints;
    float scaleFactor;

	void createBuffers3();
	void calculateBounds3();
	
	glm::vec3 boundsMin, boundsMax, avgCenter;

    
};

//BOOST_CLASS_EXPORT_KEY(Mesh);


#endif

