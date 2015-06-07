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



/** Mesh is an Asset that represents a 3D Model. The vertexes are indexed, meaning that they're stored once only
	and can be referenced in several faces (triangles).

	Currently supported features:
	-Vertex Position
	-Vertex UV
	-Vertex Normal

	Animations are NOT currently supported.
*/
class Mesh : public Asset
#ifdef GUINITY_DEBUG
	, public StaticCounter<Mesh>
#endif
{


	// TODO. ALLOWING PRIVATE BECAUSE OF SERIALIZATION. FIND OUT HOW TO USE BOOST
	// NON-INTRUSIVE SERIALIZATION WITH PRIVATE MEMBERS AND CHANGE IT
public:
	// Allow serialization to access non-public data members.  
	friend class boost::serialization::access;

	/** The vertices data */
	vector<MeshVertex> meshVertices;
	/** The mesh triangles */
	vector<unsigned short> triangles;

	/** Vertex array*/
	GLuint vao;
	/** Triangles array*/
	GLuint ibo;
	/** Vertex data array*/
	GLuint mvbo;

	/** Scale factor of the mesh */
	float scaleFactor;

	/** Min bounds of the mesh */
	glm::vec3 boundsMin;
	/** Max bounds of the mesh */
	glm::vec3 boundsMax;
	/** Average center of the mesh */
	glm::vec3 avgCenter;

public:
	/** Default Constructor */
	Mesh();
	/** Constructor from array of indices, normal points, uvs and triangles */
	Mesh(float* indices, float* normalPoints, float* uv, unsigned int *triangles, int nPoints, int nTriangles);
	/** Constructor from vector of MeshVertex and triangles */
	Mesh(vector<MeshVertex> vertex, vector<unsigned short> triangles);
	/** Constructor from vector of MeshVertex, subset of used Indexes and triangles */
	Mesh(vector<glm::vec3> vertices,vector<int> usedIndex,vector<int> usedTris);
    
	/** Default Destructor */
    virtual ~Mesh();

	/** scaleFactor Setter */
	void setScaleFactor(float f);
	/** scaleFactor getter */
	float getScaleFactor();

	/** boundsMin Getter*/
	glm::vec3 getBoundsMin();
	/** boundsMax Getter*/
	glm::vec3 getBoundsMax();
	/** avgCenter Getter*/
	glm::vec3 getAverageCenter();

	/** vao getter */
	float getVertexArrayID();
	/** mvbo getter */
	float getVertexBuffer();
	/** ibo getter */
	float getTrianglesBuffer();

	/** Count of triangles list  */
	int getTrianglesCount();
	/** Count of Mesh Vertices */
	int getVerticesCount();

	/** Adds a new vertex to the mesh */
	void addVertex(glm::vec3 position, glm::vec2 uv, glm::vec3 normal);
	/** Adds a new index to the triangles list*/
	void addTriangle(int vertexIndex);

    void setVertices(vector<MeshVertex> meshVertices);
    void setTriangles(vector<unsigned short> triangles);
    
	
	/** Create OpenGL buffers */
	void createBuffers();
	/** Calculate mesh bounds */
	void calculateBounds();

    
	/** Returns non duplicate mesh vertices based on position only. It does not take into consideration other parameters such as UV or normal.
		This function was used by the ConvexHull in Math.hpp */
    vector<glm::vec3> getNonDuplicateMeshVertex();


};



#endif

