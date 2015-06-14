#include "Mesh.hpp"
#include <math.h>
#include <glm/geometric.hpp>
#include "GraphicsSystem.hpp"
#include <map>

/** Default Constructor */
Mesh::Mesh() : Asset()
{
    
    mvbo = vao  = ibo = 0;
    scaleFactor = 1;
    
#ifdef GUINITY_DEBUG
	nCount++;
#endif
    
}


/** Constructor from array of vertices, normal points, uvs and triangle indices. The arrays should contain 3 indices per vertex for the position and normal points and 2 indices per vertex for the UV. The triangles array uses 3 elements per triangle.
 
 @param[in] vertices the vertices, 3 elements per vertex
 @param[in] normalPoints the normals, 3 elements per vertex
 @param[in] uvs the UVs, 2 elements per vertex
 @param[in] triangles the triangles that form the Mesh
 @param[in] nVertices the vertex count
 @param[in] nTriangles the size of the triangles array
 */
Mesh::Mesh(float* vertices, float* normalPoints, float* uv, unsigned int *triangles, int nVertices, int nTriangles)
: mvbo{0}, vao{0}, ibo{0}, scaleFactor{1}
{
    
	for (int i = 0; i < nVertices; i++)
	{
		meshVertices.push_back(MeshVertex(glm::vec3(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]),
                                          glm::vec2(uv[i * 3], uv[i * 3 + 1]),
                                          glm::vec3(normalPoints[i * 3], normalPoints[i * 3 + 1], normalPoints[i * 3 + 2])));
	}
    
	for (int i = 0; i < nTriangles; i++)
	{
		this->triangles.push_back(triangles[i]);
	}
    
#ifdef GUINITY_DEBUG
	nCount++;
#endif
    
	createBuffers();
}

/** Constructor from vector of MeshVertex and triangles
 @param[in] vertices a list of the vertices
 @param[in] triangles a list of the triangles with indexed vertices
 */
Mesh::Mesh(vector<MeshVertex> vertices, vector<unsigned short> triangles)
: mvbo{0}, vao{0}, ibo{0}, scaleFactor{1}
{
    
    
    meshVertices = std::move(vertices);
    this->triangles = std::move(triangles);
    
#ifdef GUINITY_DEBUG
	nCount++;
#endif
    
    createBuffers();
}

/** Constructor from vector of MeshVertex and triangles
 @param[in] vertices a list of vertices
 @param[in] the indices of the vertices that should be used, the ones that are not in this list are ignored
 @param[in] triangles a list of the triangles with indexed vertices
 */
Mesh::Mesh(vector<glm::vec3> vertices,vector<int> usedIndices,vector<int> triangles)
: mvbo{0}, vao{0}, ibo{0}, scaleFactor{1}
{
    
    for (int i = 0; i < usedIndices.size(); i++)
	{
		meshVertices.push_back(MeshVertex(vertices[i],glm::vec2(0,0),glm::vec3(0,0,0)));
	}
    
    for (int i = 0; i < triangles.size(); i++)
	{
        triangles.push_back(triangles[i]);
	}
    
#ifdef GUINITY_DEBUG
    nCount++;
#endif
    
    
    createBuffers();
    
}


/** Default Destructor */
Mesh::~Mesh()
{
    
	if (!triangles.empty())
	{
		GraphicsSystem::getInstance()->deleteBuffer(1, ibo);
	}
	if (!meshVertices.empty())
	{
        
		GraphicsSystem::getInstance()->deleteBuffer(1, ibo);
	}
    
    
    
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "Mesh destroyed (" << nCount << " remaining)" << endl;
#endif
    
}


/** scaleFactor Setter
 @param[in] f the scale of the imported Mesh. Recreates the vertices buffer and recalculates bounds
 */
void Mesh::setScaleFactor(float f)
{
    scaleFactor = f;
    
	for (auto &x : meshVertices)
		x.position *= f;
    
	if (mvbo != 0)
	{
        GraphicsSystem::getInstance()->deleteBuffer(1,mvbo);
		mvbo = 0;
	}
    
    GraphicsSystem::getInstance()->generateBuffer(1,mvbo,GL_ARRAY_BUFFER,meshVertices.size() * sizeof(MeshVertex),&meshVertices[0],GL_STATIC_DRAW);
    
	boundsMin *= f;
	boundsMax *= f;
	avgCenter *= f;
}
/** scaleFactor Getter
 @return the scale of the imported Mesh
 */
float Mesh::getScaleFactor()const
{
	return scaleFactor;
}


/** boundsMin Getter*/
glm::vec3 Mesh::getBoundsMin()const
{
	return boundsMin;
}
/** boundsMax Getter*/
glm::vec3 Mesh::getBoundsMax()const
{
	return boundsMax;
}

/** avgCenter Getter*/
glm::vec3 Mesh::getAverageCenter()const
{
	return avgCenter;
}


/** vao getter
 @return the OpenGL-specific vertex array buffer ID
 */
float Mesh::getVertexArrayID()const
{
	return vao;
}
/** mvbo getter
 @return the OpenGL-specific vertex data buffer ID
 */
float Mesh::getVertexBuffer()const
{
	return mvbo;
}
/** mvbo getter
 @return the OpenGL-specific indices buffer ID
 */
float Mesh::getTrianglesBuffer()const
{
	return ibo;
}


/** Count of triangles list
 @return number of triangles in the Mesh
 */
int Mesh::getTrianglesCount()const
{
	return triangles.size();
}
/** Count of Mesh Vertices
 @return number of vertices in the Mesh
 */
int Mesh::getVerticesCount()const
{
	return meshVertices.size();
}


/** Adds a new vertex to the mesh
 @param[in] position the position
 @param[in] uv the UV coordinate
 @param[in] normal the normal
 */
void Mesh::addVertex(glm::vec3 position, glm::vec2 uv, glm::vec3 normal)
{
	
    meshVertices.push_back(MeshVertex(position, uv, normal));
    
}

/** Adds a new index to the triangles list
 @param[in] vertexIndex the index of the vertex*/
void Mesh::addTriangle(int vertexIndex)
{
	triangles.push_back(vertexIndex);
}

/** Adds a new triangle to the triangles list
 @param[in] vertexIndex1 the index of the first vertex of the triangle
 @param[in] vertexIndex2 the index of the second vertex of the triangle
 @param[in] vertexIndex3 the index of the third vertex of the triangle
 */
void Mesh::addTriangle(int vertexIndex1,int vertexIndex2,int vertexIndex3)
{
	triangles.push_back(vertexIndex1);
    triangles.push_back(vertexIndex2);
    triangles.push_back(vertexIndex3);
}

/** meshVertices Setter
 @param meshVertices the vertices of the Mesh */
void Mesh::setVertices(vector<MeshVertex> meshVertices)
{
    this->meshVertices = meshVertices;
}

/** triangles Setter
 @param triangles the triangles of the Mesh */

void Mesh::setTriangles(vector<unsigned short> triangles)
{
    assert(triangles.size()%3==0);
    
    this->triangles = triangles;
}




/** Create OpenGL-specific buffers */
void Mesh::createBuffers()
{
	//nPoints = meshVertices.size();
    
	vao = 0;
    GraphicsSystem::getInstance()->generateVertexArrays(1,vao);
    
	mvbo = 0;
    GraphicsSystem::getInstance()->generateBuffer(1,mvbo,GL_ARRAY_BUFFER,meshVertices.size() * sizeof(MeshVertex),&meshVertices[0],GL_STATIC_DRAW);
    
	ibo = 0;
    GraphicsSystem::getInstance()->generateBuffer(1,ibo,GL_ELEMENT_ARRAY_BUFFER,triangles.size() * sizeof(unsigned short),&triangles[0],GL_STATIC_DRAW);
    
	calculateBounds();
}


/** Calculate mesh bounds */
void Mesh::calculateBounds()
{
	float minX, minY, minZ, maxX, maxY, maxZ;
    
	minX = meshVertices[0].position.x;
	minY = meshVertices[0].position.y;
	minZ = meshVertices[0].position.z;
    
	maxX = meshVertices[0].position.x;
	maxY = meshVertices[0].position.y;
	maxZ = meshVertices[0].position.z;
    
	glm::vec3 sumPoints = meshVertices[0].position;
    
	for (int i = 1; i < meshVertices.size(); i++)
	{
		minX = std::fminf(minX, meshVertices[i].position.x);
		minY = std::fminf(minY, meshVertices[i].position.y);
		minZ = std::fminf(minZ, meshVertices[i].position.z);
        
		maxX = std::fmaxf(maxX, meshVertices[i].position.x);
		maxY = std::fmaxf(maxY, meshVertices[i].position.y);
		maxZ = std::fmaxf(maxZ, meshVertices[i].position.z);
        
		sumPoints += meshVertices[i].position;
        
	}
    
	boundsMin = glm::vec3(minX, minY, minZ);
	boundsMax = glm::vec3(maxX, maxY, maxZ);
	avgCenter = sumPoints * (1.0f / meshVertices.size());
}

/** Returns non duplicate mesh vertices based on position only. It does not take into consideration other parameters such as UV or normal.
 This function was used by the ConvexHull in Math.hpp */
vector<glm::vec3> Mesh::getNonDuplicateMeshVertex()
{
    vector<glm::vec3> result;
    
    for (auto &vertice : meshVertices)
    {
        glm::vec3 pos =vertice.position;
        
        if(find(result.begin(),result.end(),pos) == result.end())
            result.push_back(pos);
    }
    
    
    return result;
}
