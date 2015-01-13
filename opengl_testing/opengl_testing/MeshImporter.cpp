#include "MeshImporter.hpp"
#include "Mesh.hpp"
#include <map>


MeshImporter::MeshImporter()
{
}


MeshImporter::~MeshImporter()
{
}

void MeshImporter::init()
{
	fbxManager = FbxManager::Create();
	ios = FbxIOSettings::Create(fbxManager, IOSROOT);
	fbxManager->SetIOSettings(ios);
	lImporter = FbxImporter::Create(fbxManager, "");

	

}

void MeshImporter::shutdown()
{
	lImporter->Destroy();
	fbxManager->Destroy();
}

void MeshImporter::getVertexData(FbxMesh* m_pMesh, int uPoly, int uVertex, FbxVector4& fbxVertex, FbxVector4&  fbxNormal, FbxVector2& fbxUV)
{
	// Get corresponding vertex index for this poly-vertex
	int uVertexIndex = m_pMesh->GetPolygonVertex(uPoly, uVertex);
	assert(uVertexIndex != -1 && "Index is out of range");

	// Get vertex position
	fbxVertex = m_pMesh->GetControlPointAt(uVertexIndex);

	bool bResult = m_pMesh->GetPolygonVertexNormal(uPoly, uVertex, fbxNormal);
    
    FbxStringList UVSetNameList;
    m_pMesh->GetUVSetNames( UVSetNameList );
    
    bool unmapped;
    
    bResult = m_pMesh->GetPolygonVertexUV(uPoly, uVertex,UVSetNameList.GetStringAt(0), fbxUV, unmapped);

//    m_pMesh->GetPolygonv
}

shared_ptr<Mesh> MeshImporter::importFbxMesh(string filename)
{

	string lFilename = CommonData(filename);

	// Initialize the importer.
	bool lImportStatus = lImporter->Initialize(lFilename.c_str(), -1, fbxManager->GetIOSettings());
	if (!lImportStatus) {
		printf("Call to FbxImporter::Initialize() failed.\n");
		printf("Error returned: %s\n\n", lImporter->GetStatus().GetErrorString());
		exit(-1);
	}

	// Create a new scene so it can be populated by the imported file.
	FbxScene* lScene = FbxScene::Create(fbxManager, "myScene");

	// Import the contents of the file into the scene.
	lImporter->Import(lScene);

	FbxNode* pNode = lScene->GetRootNode();

	FbxGeometryConverter* converter = new FbxGeometryConverter(fbxManager);
	converter->Triangulate(lScene, false);

	shared_ptr<Mesh> mesh = make_shared<Mesh>();
	if (pNode)
	{
		for (int nNode = 0; nNode < pNode->GetChildCount(); nNode++)
		{
			FbxNode* pChildNode = pNode->GetChild(nNode);

			

			// Search for mesh node
			if (pChildNode->GetNodeAttribute())
			{
				if (pChildNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
				{

					FbxMesh* m_pMesh = (FbxMesh*)pChildNode->GetNodeAttribute();
			
					unsigned long uPolyCount = m_pMesh->GetPolygonCount();
					unsigned long uVertexCount = 0;
					unsigned long uVertexNumber = 0;

					std::map<PackedFBXVertex, unsigned short> vertexMap;

					for (unsigned long uPoly = 0; uPoly < uPolyCount; ++uPoly)
					{
						// Get number of vertices in current poly - is your mesh triangulated?
						uVertexCount = m_pMesh->GetPolygonSize(uPoly);

						for (unsigned long uVertex = 0; uVertex < uVertexCount; ++uVertex)
						{
		
							FbxVector4 fbxVertex, fbxNormal;
							FbxVector2 fbxUV;

                            
							getVertexData(m_pMesh, uPoly, uVertex, fbxVertex, fbxNormal, fbxUV);

							PackedFBXVertex v;
							v.normal = fbxNormal;
							v.position = fbxVertex;
							v.uv = fbxUV;

							unsigned short index = 0;

							bool found = findVertex(vertexMap, v, index);

							if (!found)
							{
								mesh->addVertex(glm::vec3(fbxVertex.mData[0], fbxVertex.mData[1], fbxVertex.mData[2]),
									glm::vec2(fbxUV.mData[0], fbxUV.mData[1]),
									glm::vec3(fbxNormal.mData[0], fbxNormal.mData[1], fbxNormal.mData[2]));
								
								unsigned short newIndex = mesh->meshVertices.size() - 1;
					
								vertexMap[v] = newIndex;
								mesh->addTriangle(newIndex);
							}
							else
							{
								mesh->addTriangle(index);
							}

							// etc..
						}
					}

				}
			}
		}
	}
	//mesh->scale(0.1f);
	mesh->createBuffers3();

	lScene->Destroy();
	delete converter;

	return mesh;
}

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
		int res = fscanf(file, "%s", lineHeader, 128);
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

template<typename T>
bool MeshImporter::findVertex(std::map<T, unsigned short>& vertexMap, T& v, unsigned short& index)
{
	typename std::map<T, unsigned short>::iterator it = vertexMap.find(v);
	if (it == vertexMap.end()){
		return false;
	}
	else{
		index = it->second;
		return true;
	}
}

shared_ptr<Mesh> MeshImporter::importObjMesh(string filename)
{
	shared_ptr<Mesh> mesh = make_shared<Mesh>();

	vector <glm::vec3>out_vertices;
	vector <glm::vec2>out_uvs;
	vector <glm::vec3>out_normals;


	bool loaded = loadOBJ(CommonData(filename).c_str(), out_vertices, out_uvs, out_normals);

	std::map<PackedOBJVertex, unsigned short> vertexMap;

	for (int i = 0; i < out_vertices.size(); i++)
	{

		PackedOBJVertex v;
		v.normal = out_normals[i];
		v.position = out_vertices[i];
		v.uv = out_uvs[i];

		unsigned short index = 0;

		bool found = findVertex(vertexMap, v, index);

		if (!found)
		{
			mesh->addVertex(v.position, v.uv, v.normal);

			unsigned short newIndex = mesh->meshVertices.size() - 1;

			vertexMap[v] = newIndex;
			mesh->addTriangle(newIndex);
		}
		else
		{
			mesh->addTriangle(index);
		}
	}

	mesh->createBuffers3();

	return mesh;
}