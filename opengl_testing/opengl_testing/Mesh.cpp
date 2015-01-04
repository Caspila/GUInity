#include "Mesh.hpp"
#include <math.h>
#include <glm/geometric.hpp>


// Code from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/


//BOOST_CLASS_EXPORT_IMPLEMENT(Asset);

Mesh::Mesh() : Asset()
{
    
	 mvbo = vao  = ibo = 0;


#ifdef GUINITY_DEBUG
	nCount++;
#endif

}


Mesh::Mesh(float* indices, float* normalPoints, float* uv, unsigned int *triangles, int nPoints, int nTriangles) : Asset()
{
	mvbo = vao = ibo = 0;
    
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


void Mesh::addVertex(glm::vec3 position, glm::vec2 uv, glm::vec3 normal)
{
	//int vertexIndex=	vertexExists(position, uv, normal);
	//
	//if (vertexIndex == -1)
	//{
		meshVertices.push_back(MeshVertex(position, uv, normal));
	//	return meshVertices.size() - 1;
	//}
	//else
	//	return vertexIndex;
		
}

void Mesh::addTriangle(int vertexIndex)
{
	triangles.push_back(vertexIndex);
}

void Mesh::setScaleFactor(float f)
{
    scaleFactor = f;
    
	for (auto &x : meshVertices)
		x.position *= f;

	if (mvbo != 0)
	{
		glDeleteBuffers(1, &mvbo);
		mvbo = 0;
	}

	glGenBuffers(1, &mvbo);
	glBindBuffer(GL_ARRAY_BUFFER, mvbo);
	glBufferData(GL_ARRAY_BUFFER, meshVertices.size() * sizeof(MeshVertex), &meshVertices[0], GL_STATIC_DRAW);

	boundsMin *= f;
	boundsMax *= f;
	avgCenter *= f;
}


void Mesh::createBuffers3()
{
	//nPoints = meshVertices.size();

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	mvbo = 0;
	glGenBuffers(1, &mvbo);
	glBindBuffer(GL_ARRAY_BUFFER, mvbo);
	glBufferData(GL_ARRAY_BUFFER, meshVertices.size() * sizeof(MeshVertex), &meshVertices[0], GL_STATIC_DRAW);

	ibo = 0;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(unsigned short), &triangles[0], GL_STATIC_DRAW);

	calculateBounds3();
}

Mesh::~Mesh()
{

	if (!triangles.empty())
	{
		glDeleteBuffers(1, &ibo);
	}
	if (!meshVertices.empty())
	{
		glDeleteBuffers(1, &mvbo);
	}
	glDeleteVertexArrays(1, &vao);


#ifdef GUINITY_DEBUG
	nCount--;
	cout << "Mesh destroyed (" << nCount << " remaining)" << endl;
#endif
	
}


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

