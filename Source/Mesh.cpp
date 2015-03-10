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


/** Constructor from array of indices, normal points, uvs and triangles */
Mesh::Mesh(float* indices, float* normalPoints, float* uv, unsigned int *triangles, int nPoints, int nTriangles) : Asset()
{
	mvbo = vao = ibo = 0;
	scaleFactor = 1;

	//this->nPoints = nPoints;

	for (int i = 0; i < nPoints; i++)
	{
		meshVertices.push_back(MeshVertex(glm::vec3(indices[i * 3], indices[i * 3 + 1], indices[i * 3 + 2]),
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

	createBuffers3();
}

/** Constructor from vector of MeshVertex and triangles */
Mesh::Mesh(vector<MeshVertex> vertex, vector<unsigned short> triangles)
{
    
    mvbo = vao = ibo = 0;
    scaleFactor = 1;

    meshVertices = std::move(vertex);
    this->triangles = std::move(triangles);
    
#ifdef GUINITY_DEBUG
	nCount++;
#endif
    
    createBuffers3();
}

/** Constructor from vector of MeshVertex, subset of used Indexes and triangles */
Mesh::Mesh(vector<glm::vec3> vertices,vector<int> usedIndex,vector<int> usedTris)
{
   	mvbo = vao = ibo = 0;
        scaleFactor = 1;

    for (int i = 0; i < usedIndex.size(); i++)
	{
		meshVertices.push_back(MeshVertex(vertices[i],glm::vec2(0,0),glm::vec3(0,0,0)));
	}

    for (int i = 0; i < usedTris.size(); i++)
	{
        triangles.push_back(usedTris[i]);
	}
    
#ifdef GUINITY_DEBUG
    nCount++;
#endif
                               
                               
    createBuffers3();
    
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


/** Adds a new vertex to the mesh */
void Mesh::addVertex(glm::vec3 position, glm::vec2 uv, glm::vec3 normal)
{
	
		meshVertices.push_back(MeshVertex(position, uv, normal));
		
}

/** Adds a new index to the triangles list*/
void Mesh::addTriangle(int vertexIndex)
{
	triangles.push_back(vertexIndex);
}

/** scaleFactor Setter */
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
/** scaleFactor getter */
float Mesh::getScaleFactor()
{
	return scaleFactor;
}

/** boundsMin Getter*/
glm::vec3 Mesh::getBoundsMin()
{
	return boundsMin;
}
/** boundsMax Getter*/
glm::vec3 Mesh::getBoundsMax()
{
	return boundsMax;
}

/** avgCenter Getter*/
glm::vec3 Mesh::getAverageCenter()
{
	return avgCenter;
}


/** vao getter */
float Mesh::getVertexArrayID()
{
	return vao;
}
/** mvbo getter */
float Mesh::getVertexBuffer()
{
	return mvbo;
}
/** ibo getter */
float Mesh::getTrianglesBuffer()
{
	return ibo;
}

/** Count of triangles list getter */
int Mesh::getTrianglesCount()
{
	return triangles.size();
}
/** Count of Mesh Vertices */
int Mesh::getVerticesCount()
{
	return meshVertices.size();
}

/** Create OpenGL buffers */
void Mesh::createBuffers3()
{
	//nPoints = meshVertices.size();

	vao = 0;
    GraphicsSystem::getInstance()->generateVertexArrays(1,vao);

	mvbo = 0;
    GraphicsSystem::getInstance()->generateBuffer(1,mvbo,GL_ARRAY_BUFFER,meshVertices.size() * sizeof(MeshVertex),&meshVertices[0],GL_STATIC_DRAW);

	ibo = 0;
    GraphicsSystem::getInstance()->generateBuffer(1,ibo,GL_ELEMENT_ARRAY_BUFFER,triangles.size() * sizeof(unsigned short),&triangles[0],GL_STATIC_DRAW);

	calculateBounds3();
}


/** Calculate mesh bounds */
void Mesh::calculateBounds3()
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
