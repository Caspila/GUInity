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

/** A mesh vertex structure that contains position, UV coordinates and normal */
struct MeshVertex
{
    /** The position */
	glm::vec3 position;
    /** The UV coordinates */
	glm::vec2 uv;
    /** The normal */
	glm::vec3 normal;
    
    /** Constructor
     @param[in] position the position
     @param[in] uv the UV coordinates
     @param[in] normal the normal
     */
	MeshVertex(glm::vec3 position, glm::vec2 uv, glm::vec3 normal) : position(position), uv(uv), normal(normal) {}
	MeshVertex(){}
	
};



/** Mesh is an Asset that represents a 3D Model. The vertexes are indexed, meaning that they're stored once only
 and can be referenced in several faces (triangles).
 
 Currently supported features:
 -Vertex Position
 -Vertex UV
 -Vertex Normal
 
 Animations are currently NOT supported.
 */
class Mesh : public Asset
#ifdef GUINITY_DEBUG
, public StaticCounter<Mesh>
#endif
{
    
    
	// TODO. ALLOWING PUBLIC BECAUSE OF SERIALIZATION. FIND OUT HOW TO USE BOOST
	// NON-INTRUSIVE SERIALIZATION WITH PRIVATE MEMBERS AND CHANGE IT
public:
    
	/** The vertices data */
	vector<MeshVertex> meshVertices;
	/** The mesh triangles */
	vector<unsigned short> triangles;
    
	/** Vertex array Buffer. OpenGL specific */
	GLuint vao;
	/** Triangles array Buffer. OpenGL specific */
	GLuint ibo;
	/** Vertex data array Buffer. OpenGL specific */
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
	/** Constructor from array of vertices, normal points, uvs and triangle indices. The arrays should contain 3 indices per vertex for the position and normal points and 2 indices per vertex for the UV. The triangles array uses 3 elements per triangle.
     
     @param[in] vertices the vertices, 3 elements per vertex
     @param[in] normalPoints the normals, 3 elements per vertex
     @param[in] uvs the UVs, 2 elements per vertex
     @param[in] triangles the triangles that form the Mesh
     @param[in] nVertices the vertex count
     @param[in] nTriangles the size of the triangles array
     */
	Mesh(float* vertices, float* normalPoints, float* uv, unsigned int *triangles, int nVertices, int nTriangles);
	/** Constructor from vector of MeshVertex and triangles
     @param[in] vertices a list of the vertices
     @param[in] triangles a list of the triangles with indexed vertices
     */
	Mesh(vector<MeshVertex> vertices, vector<unsigned short> triangles);
	/** Constructor from vector of MeshVertex and triangles
     @param[in] vertices a list of vertices
     @param[in] the indices of the vertices that should be used, the ones that are not in this list are ignored
     @param[in] triangles a list of the triangles with indexed vertices
     */
    Mesh(vector<glm::vec3> vertices,vector<int> usedIndices,vector<int> triangles);
    
	/** Default Destructor */
    virtual ~Mesh();
    
	/** scaleFactor Setter
     @param[in] f the scale of the imported Mesh. Recreates the vertices buffer and recalculates bounds
     */
	void setScaleFactor(float f);
	/** scaleFactor Getter
     @return the scale of the imported Mesh
     */
	float getScaleFactor() const;
    
	/** boundsMin Getter*/
	glm::vec3 getBoundsMin() const;
	/** boundsMax Getter*/
	glm::vec3 getBoundsMax() const;
	/** avgCenter Getter*/
	glm::vec3 getAverageCenter() const;
    
    /** vao getter
     @return the OpenGL-specific vertex array buffer ID
     */
	float getVertexArrayID() const;
    /** mvbo getter
     @return the OpenGL-specific vertex data buffer ID
     */
	float getVertexBuffer() const;
    /** mvbo getter
     @return the OpenGL-specific indices buffer ID
     */
	float getTrianglesBuffer() const;
    
	/** Count of triangles list
     @return number of triangles in the Mesh
     */
	int getTrianglesCount() const;
	/** Count of Mesh Vertices
     @return number of vertices in the Mesh
     */
	int getVerticesCount() const;
    
	/** Adds a new vertex to the mesh
     @param[in] position the position
     @param[in] uv the UV coordinate
     @param[in] normal the normal
     */
	void addVertex(glm::vec3 position, glm::vec2 uv, glm::vec3 normal);
	/** Adds a new index to the triangles list
     @param[in] vertexIndex the index of the vertex*/
	void addTriangle(int vertexIndex);
    
    /** Adds a new triangle to the triangles list
     @param[in] vertexIndex1 the index of the first vertex of the triangle
     @param[in] vertexIndex2 the index of the second vertex of the triangle
     @param[in] vertexIndex3 the index of the third vertex of the triangle
     */
	void addTriangle(int vertexIndex1,int vertexIndex2,int vertexIndex3);
    
    
    /** meshVertices Setter
     @param meshVertices the vertices of the Mesh */
    void setVertices(vector<MeshVertex> meshVertices);
    /** triangles Setter
     @param triangles the triangles of the Mesh */
    void setTriangles(vector<unsigned short> triangles);
    
	
	/** Create OpenGL-specific buffers */
	void createBuffers();
	/** Calculate mesh bounds */
	void calculateBounds();
    
    
	/** Returns non duplicate mesh vertices based on position only. It does not take into consideration other parameters such as UV or normal.
     This function was used by the ConvexHull in Math.hpp */
    vector<glm::vec3> getNonDuplicateMeshVertex();
    
    
};



#endif

