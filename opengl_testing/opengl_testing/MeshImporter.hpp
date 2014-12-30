#pragma once

#include "Module.hpp"
#include <fbxsdk.h>
#include <glm/common.hpp>
#include <glm/geometric.hpp>
#include <map>

using namespace fbxsdk_2015_1;

class Mesh;

// Fastvbo indexer idea: https://code.google.com/p/opengl-tutorial-org/source/browse/common/vboindexer.cpp
struct PackedFBXVertex{
	FbxVector4 position;
	FbxVector2 uv;
	FbxVector4 normal;
	bool operator<(const PackedFBXVertex that) const{
		return memcmp((void*)this, (void*)&that, sizeof(PackedFBXVertex))>0;
	};
};
struct PackedOBJVertex{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
	bool operator<(const PackedOBJVertex that) const{
		return memcmp((void*)this, (void*)&that, sizeof(PackedOBJVertex))>0;
	};
};

class MeshImporter
{
public:
	MeshImporter();
	~MeshImporter();

	void init();
	void shutdown();
	shared_ptr<Mesh> importFbxMesh(string filename);
	shared_ptr<Mesh> importObjMesh(string filename);

	void getVertexData(FbxMesh* m_pMesh, int uPoly, int uVertex, FbxVector4& fbxVertex, FbxVector4&  fbxNormal, FbxVector2& fbxUV);

	template<typename T>
	bool findVertex(std::map<T, unsigned short>& vertexMap, T& v, unsigned short& index);

	FbxManager* fbxManager;
	FbxIOSettings * ios;
	FbxImporter* lImporter;
};

