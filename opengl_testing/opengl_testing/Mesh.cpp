#include "Mesh.hpp"
#include <math.h>


// Code from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
bool loadOBJ(const char* path, std::vector <glm::vec3>& out_vertices, std::vector <glm::vec2>& out_uvs, std::vector <glm::vec3>& out_normals)
{
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE * file = fopen(path, "r");
	
	while (1){

		//cout << file->_tmpfname << endl;
		char lineHeader[128];
		// read the first word of the line
        int res = fscanf(file, "%s", lineHeader,128);
		//int res = fscanf_s(file, "%s", lineHeader, 128);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		if (strcmp(lineHeader, "v") == 0){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9){
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);

		}
	}
		// For each vertex of each triangle
		for (unsigned int i = 0; i < vertexIndices.size(); i++){
			unsigned int vertexIndex = vertexIndices[i];
			glm::vec3 vertex = temp_vertices[vertexIndex - 1];
			//vertex = vertex * 0.5f;
			out_vertices.push_back(vertex);
		}
		for (unsigned int i = 0; i < uvIndices.size(); i++){
			unsigned int uvIndex = uvIndices[i];
			glm::vec2 uv = temp_uvs[uvIndex - 1];
			out_uvs.push_back(uv);
		}
		for (unsigned int i = 0; i < normalIndices.size(); i++){
			unsigned int normalIndex = normalIndices[i];
			glm::vec3 normal = temp_normals[normalIndex - 1];
			out_normals.push_back(normal);
		}

		return true;
}


Mesh::Mesh(float *points, int nPoints, float* colorPoints, float* normalPoints)
{
	//int realPoints = nPoints * 3;

	this->nPoints = nPoints;

	for (int i = 0; i < nPoints; i++)
	{
		this->points.push_back(glm::vec3(points[i * 3], points[i * 3 + 1], points[i * 3 + 2]));
		this->normalPoints.push_back(glm::vec3(normalPoints[i * 3], normalPoints[i * 3 + 1], normalPoints[i * 3 + 2]));
	}

#ifdef GUINITY_DEBUG
	nCount++;
#endif

	createBuffers();
}

Mesh::Mesh(const char* path)
{
	
	bool loaded = loadOBJ(path, points, uv, normalPoints);

	if (loaded)
	{
		nPoints = (int)points.size();

		createBuffers();
	}

#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

void Mesh::createBuffers()
{
	vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, nPoints * 3 * sizeof(float), &points[0], GL_STATIC_DRAW);

	if (!colorPoints.empty())
	{
		cbo = 0;
		glGenBuffers(1, &cbo);
		glBindBuffer(GL_ARRAY_BUFFER, cbo);
		glBufferData(GL_ARRAY_BUFFER, nPoints * 3 * sizeof(float), &colorPoints[0], GL_STATIC_DRAW);
	}

	if (!normalPoints.empty())
	{
		nbo = 0;
		glGenBuffers(1, &nbo);
		glBindBuffer(GL_ARRAY_BUFFER, nbo);
		glBufferData(GL_ARRAY_BUFFER, nPoints * 3 * sizeof(float), &normalPoints[0], GL_STATIC_DRAW);
	}

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	if(!colorPoints.empty())
	{
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, cbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	}
	if (!normalPoints.empty())
	{
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, nbo);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	}


	calculateBounds();
}



Mesh::~Mesh()
{
	glDeleteBuffers(1, &vbo);
	if (!normalPoints.empty())
	{
		glDeleteBuffers(1, &nbo);
	}
	if (!colorPoints.empty())
	{
		glDeleteBuffers(1, &cbo);
	}
	glDeleteVertexArrays(1, &vao);


#ifdef GUINITY_DEBUG
	nCount--;
	cout << "Mesh destroyed (" << nCount << " remaining)" << endl;
#endif
	
}



void Mesh::calculateBounds()
{
	float minX, minY, minZ, maxX, maxY, maxZ;

	minX = points[0].x;
	minY = points[0].y;
	minZ = points[0].z;

	maxX = points[0].x;
	maxY = points[0].y;
	maxZ = points[0].z;

	for (int i = 1; i < nPoints; i++)
	{
		minX = std::fminf(minX, points[i].x);
		minY = std::fminf(minY, points[i].y);
		minZ = std::fminf(minZ, points[i].z);

		maxX = std::fmaxf(maxX, points[i].x);
		maxY = std::fmaxf(maxY, points[i].y);
		maxZ = std::fmaxf(maxZ, points[i].z);

	}

	boundsMin = glm::vec3(minX, minY, minZ);
	boundsMax = glm::vec3(maxX, maxY, maxZ);
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