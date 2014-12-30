#include "Mesh.hpp"
#include <math.h>
#include <glm/geometric.hpp>


// Code from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/


Mesh::Mesh()
{
	 mvbo = vao  = ibo = 0;


#ifdef GUINITY_DEBUG
	nCount++;
#endif

}

	//
	//
	//bool Mesh::closeEnough(MeshVertex& v, glm::vec3& point, glm::vec2& uv, glm::vec3& normal)
	//{
	//	if (glm::length(v.position - point) < 0.01f &&
	//		glm::length(v.normal - normal) < 0.01f &&
	//		glm::length(v.uv - uv) < 0.01f)
	//		return true;
	//	return false;
	//
	//		return true;
	//}
	////
	////int Mesh::vertexExists(glm::vec3& vec3, glm::vec2& uv, glm::vec3& normal)
	////{
	////	int cont = 0;
	////	for (auto&x : meshVertices)
	////	{
	////		if (closeEnough(x, vec3, uv, normal))
	////			return cont;
	////		cont++;
	////	}
	////
	////	return -1;
	////}

//
//unsigned short Mesh::getVertexIndex(glm::vec3& vec3, glm::vec2& uv, glm::vec3& normal)
//{
//	unsigned short cont = 0;
//	for (auto&x : meshVertices)
//	{
//		if (closeEnough(x, vec3, uv, normal))
//			return cont;
//		cont++;
//	}
//
//	cerr << "Could not find vertex!" << endl;
//
//	return 0;
//}
//MeshVertex Mesh::getVertex(glm::vec3& vec3, glm::vec2& uv, glm::vec3& normal)
//{
//	for (auto&x : meshVertices)
//		if (closeEnough(x, vec3, uv, normal))
//			return x;
//
//	cerr << "Could not find vertex!" << endl;
//
//	return MeshVertex();
//}

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

//void Mesh::addTriangle(glm::vec3 position, glm::vec2 uv, glm::vec3 normal)
//{
//	unsigned short v1 = getVertexIndex(position, uv, normal);
//	
//	triangles.push_back(v1);
//}
//
//void Mesh::addTriangle(glm::vec3 position, glm::vec2 uv, glm::vec3 normal,
//	glm::vec3 position2, glm::vec2 uv2, glm::vec3 normal2, 
//	glm::vec3 position3, glm::vec2 uv3, glm::vec3 normal3)
//{
//
//	unsigned short v1 = getVertexIndex(position, uv, normal);
//	unsigned short v2 = getVertexIndex(position2, uv2, normal2);
//	unsigned short v3 = getVertexIndex(position3, uv3, normal3);
//
//	triangles.push_back(v1);
//	triangles.push_back(v2);
//	triangles.push_back(v3);
//}

void Mesh::scale(float f)
{
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

//Mesh::Mesh(float *points, int nPoints, float* colorPoints, float* normalPoints)
//{
//	mvbo = vao = ibo = 0;
//	//int realPoints = nPoints * 3;
//
//	this->nPoints = nPoints;
//
//	for (int i = 0; i < nPoints; i++)
//	{
//		this->points.push_back(glm::vec3(points[i * 3], points[i * 3 + 1], points[i * 3 + 2]));
//		this->normalPoints.push_back(glm::vec3(normalPoints[i * 3], normalPoints[i * 3 + 1], normalPoints[i * 3 + 2]));
//	}
//
//#ifdef GUINITY_DEBUG
//	nCount++;
//#endif
//
//	createBuffers();
//}

Mesh::Mesh(float* indices, float* normalPoints, float* uv, unsigned int *triangles, int nPoints, int nTriangles)
{
	mvbo = vao = ibo = 0;

	this->nPoints = nPoints;

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

//Mesh::Mesh(const char* path)
//{
//	vbo = mvbo = vao = nbo = cbo = ibo = 0;
//	bool loaded = loadOBJ(path, points, uv, normalPoints);
//
//	if (loaded)
//	{
//		nPoints = (int)points.size();
//
//		createBuffers();
//	}
//
//#ifdef GUINITY_DEBUG
//	nCount++;
//#endif
//}

//void Mesh::createBuffers()
//{
//	vbo = 0;
//	glGenBuffers(1, &vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBufferData(GL_ARRAY_BUFFER, nPoints * 3 *sizeof(float), &points[0], GL_STATIC_DRAW);
//
//
//	if (!colorPoints.empty())
//	{
//		cbo = 0;
//		glGenBuffers(1, &cbo);
//		glBindBuffer(GL_ARRAY_BUFFER, cbo);
//		glBufferData(GL_ARRAY_BUFFER, nPoints * 3 * sizeof(float), &colorPoints[0], GL_STATIC_DRAW);
//	}
//
//	if (!normalPoints.empty())
//	{
//		nbo = 0;
//		glGenBuffers(1, &nbo);
//		glBindBuffer(GL_ARRAY_BUFFER, nbo);
//		glBufferData(GL_ARRAY_BUFFER, nPoints * 3 * sizeof(float), &normalPoints[0], GL_STATIC_DRAW);
//	}
//
//	vao = 0;
//	glGenVertexArrays(1, &vao);
//	
//	/*glBindVertexArray(vao);
//	
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//	
//	if(!colorPoints.empty())
//	{
//		glEnableVertexAttribArray(1);
//		glBindBuffer(GL_ARRAY_BUFFER, cbo);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//	}
//	if (!normalPoints.empty())
//	{
//		glEnableVertexAttribArray(2);
//		glBindBuffer(GL_ARRAY_BUFFER, nbo);
//		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//	}
//
//*/
//	calculateBounds();
//}
//
//
//void Mesh::createBuffers2()
//{
//	vao = 0;
//	glGenVertexArrays(1, &vao);
//	glBindVertexArray(vao);
//
//	vbo = 0;
//	glGenBuffers(1, &vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBufferData(GL_ARRAY_BUFFER, nPoints * 3 * sizeof(float), &indices[0], GL_STATIC_DRAW);
//
//	nbo = 0;
//	glGenBuffers(1, &nbo);
//	glBindBuffer(GL_ARRAY_BUFFER, nbo);
//	glBufferData(GL_ARRAY_BUFFER, nPoints * 3 * sizeof(float), &normalPoints[0], GL_STATIC_DRAW);
//
//	ibo = 0;
//	glGenBuffers(1, &ibo);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(unsigned short), &triangles[0], GL_STATIC_DRAW);
//	
//	calculateBounds2();
//}
//


void Mesh::createBuffers3()
{
	nPoints = meshVertices.size();

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
	//glDeleteBuffers(1, &vbo);
	//if (!normalPoints.empty())
	//{
	//	glDeleteBuffers(1, &nbo);
	//}
	//if (!colorPoints.empty())
	//{
	//	glDeleteBuffers(1, &cbo);
	//}
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


//
//void Mesh::calculateBounds()
//{
//	float minX, minY, minZ, maxX, maxY, maxZ;
//
//	minX = points[0].x;
//	minY = points[0].y;
//	minZ = points[0].z;
//
//	maxX = points[0].x;
//	maxY = points[0].y;
//	maxZ = points[0].z;
//
//	for (int i = 1; i < nPoints; i++)
//	{
//		minX = std::fminf(minX, points[i].x);
//		minY = std::fminf(minY, points[i].y);
//		minZ = std::fminf(minZ, points[i].z);
//
//		maxX = std::fmaxf(maxX, points[i].x);
//		maxY = std::fmaxf(maxY, points[i].y);
//		maxZ = std::fmaxf(maxZ, points[i].z);
//
//	}
//
//	boundsMin = glm::vec3(minX, minY, minZ);
//	boundsMax = glm::vec3(maxX, maxY, maxZ);
//}
//
//
//void Mesh::calculateBounds2()
//{
//	float minX, minY, minZ, maxX, maxY, maxZ;
//
//	minX = indices[0].x;
//	minY = indices[0].y;
//	minZ = indices[0].z;
//
//	maxX = indices[0].x;
//	maxY = indices[0].y;
//	maxZ = indices[0].z;
//
//	for (int i = 1; i < nPoints; i++)
//	{
//		minX = std::fminf(minX, indices[i].x);
//		minY = std::fminf(minY, indices[i].y);
//		minZ = std::fminf(minZ, indices[i].z);
//
//		maxX = std::fmaxf(maxX, indices[i].x);
//		maxY = std::fmaxf(maxY, indices[i].y);
//		maxZ = std::fmaxf(maxZ, indices[i].z);
//
//	}
//
//	boundsMin = glm::vec3(minX, minY, minZ);
//	boundsMax = glm::vec3(maxX, maxY, maxZ);
//}


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

	for (int i = 1; i < nPoints; i++)
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
	avgCenter = sumPoints * (1.0f / nPoints);
}

//void Mesh::calculateBounds()
//{
//	float minX, minY, minZ, maxX, maxY, maxZ;
//
//	minX = points[0];
//	minY = points[1];
//	minZ = points[2];
//
//	maxX = points[0];
//	maxY = points[1];
//	maxZ = points[2];
//
//	for (int i = 1; i < nPoints; i++)
//	{
//		minX = std::fminf(minX, points[i * 3]);
//		minY = std::fminf(minY, points[i * 3 + 1]);
//		minZ = std::fminf(minZ, points[i * 3 + 2]);
//
//		maxX = std::fmaxf(maxX, points[i * 3]);
//		maxY = std::fmaxf(maxY, points[i * 3 + 1]);
//		maxZ = std::fmaxf(maxZ, points[i * 3 + 2]);
//
//	}
//
//	boundsMin = glm::vec3(minX, minY, minZ);
//	boundsMax = glm::vec3(maxX, maxY, maxZ);
//}