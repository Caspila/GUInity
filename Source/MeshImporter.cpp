#include "MeshImporter.hpp"
#include "Mesh.hpp"
#include "SkinnedMesh.hpp"
#include "Converter.hpp"
#include <map>
#include <glm/gtx/spline.hpp>
#include <interpolation.h>
#include "Animation.hpp"

using namespace alglib;

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
    if(!bResult)
        fbxNormal = FbxVector4(0,0,0,0);
    FbxStringList UVSetNameList;
    m_pMesh->GetUVSetNames( UVSetNameList );
    
    bool unmapped;
    
    bResult = m_pMesh->GetPolygonVertexUV(uPoly, uVertex,UVSetNameList.GetStringAt(0), fbxUV, unmapped);
    if(!bResult)
        fbxUV = FbxVector2(0,0);
    
    
    //    m_pMesh->GetPolygonv
}

void MeshImporter::importFbxSkeleton(FbxSkeleton* skeletonNode)
{
    if(!skeletonNode)
        return;
    
    
}

void MeshImporter::importFbxSkin(FbxSkin* skinNode)
{
    if(!skinNode)
        return;
    
    int nClusters = skinNode->GetClusterCount();
    
    for(int i= 0; i < nClusters; i++)
    {
        FbxCluster* cluster = skinNode->GetCluster(i);
        
        int* controlPoints = cluster->GetControlPointIndices();
        double *weigthts = cluster->GetControlPointWeights();
        for(int i = 0; i < cluster->GetControlPointIndicesCount(); i++)
        {
            cout << "Control Point index: " << controlPoints[i] <<  " weight: " << weigthts[i] << endl;
        }
    }
}

bool MeshImporter::isMeshSkinned(FbxMesh* meshNode)
{
    int deformerCount = meshNode->GetDeformerCount();
    
    for(int i = 0 ; i < deformerCount ; i ++)
    {
        FbxDeformer* deformer = meshNode->GetDeformer(i);
        
        if(deformer->GetDeformerType() == FbxDeformer::EDeformerType::eSkin)
            return true;
    }
    
    return false;
}

shared_ptr<Mesh> MeshImporter::importFbxMesh(FbxScene* scene,FbxMesh* meshNode)
{
    if(!meshNode)
        return nullptr;
    
    
    vector<MeshVertex> vertices;
    vector<unsigned short> triangles;
    
    
    unsigned long uPolyCount = meshNode->GetPolygonCount();
    unsigned long uVertexCount = 0;
    
    std::map<PackedFBXVertex, unsigned short> vertexMap;
    std::map<unsigned short, unsigned short> originalVertexToNewVertex;
    
    
    for (int uPoly = 0; uPoly < uPolyCount; ++uPoly)
    {
        // Get number of vertices in current poly - is your mesh triangulated?
        uVertexCount = meshNode->GetPolygonSize((int)uPoly);
        
        for (int uVertex = 0; uVertex < uVertexCount; ++uVertex)
        {
            
            FbxVector4 fbxVertex(0,0,0,0);// = FbxVector4(0,0,0,0);
            FbxVector4 fbxNormal(0,0,0,0);// = FbxVector4(0,0,0,0);;
            FbxVector2 fbxUV(0,0);
            
            
            
            getVertexData(meshNode, uPoly, uVertex, fbxVertex, fbxNormal, fbxUV);
            
            PackedFBXVertex v;
            v.normal = fbxNormal;
            v.position = fbxVertex;
            v.uv = fbxUV;
            
            unsigned short index = 0;
            
            bool found = findVertex(vertexMap, v, index);
            
            if (!found)
            {
                vertices.push_back(MeshVertex(glm::vec3(fbxVertex.mData[0], fbxVertex.mData[1], fbxVertex.mData[2]),glm::vec2(fbxUV.mData[0], fbxUV.mData[1]),glm::vec3(fbxNormal.mData[0], fbxNormal.mData[1], fbxNormal.mData[2])));
                
                unsigned short newIndex = vertices.size() - 1;
                
                vertexMap[v] = newIndex;
                triangles.push_back(newIndex);
                
               	int uVertexIndex = meshNode->GetPolygonVertex(uPoly, uVertex);
                originalVertexToNewVertex[uVertexIndex] = newIndex;
                
            }
            else
            {
                triangles.push_back(index);
                
                int uVertexIndex = meshNode->GetPolygonVertex(uPoly, uVertex);
                originalVertexToNewVertex[uVertexIndex] = index;
            }
            
        }
    }
    
    
    shared_ptr<Mesh> mesh = make_shared<Mesh>();
    
    
    mesh->setVertices(vertices);
    mesh->setTriangles(triangles);
    
    mesh->createBuffers();
    
    
	return mesh;
}

void MeshImporter::readFbxAnimationCurve(std::map<CurveAnimationType,AnimationCurve>& animationMap, CurveAnimationType animationType, FbxAnimCurve* fbxCurve)
{
    if(!fbxCurve)
        return;
    
    AnimationCurve animationCurve;
    
    int keyFrameCount = fbxCurve->KeyGetCount();
    for(int x = 0; x < keyFrameCount; x++)
    {
        FbxAnimCurveKey curveKey = fbxCurve->KeyGet(x);
        
        int pHour, pMinute, pSecond, pFrame, pField, pResidual;
        
        FbxTime time = curveKey.GetTime();
        
//        int nFrames = time.GetFrameCount();
        
//        double frameRate = time.GetFrameRate(FbxTime::EMode::eDefaultMode);
        
        time.GetTime(pHour, pMinute, pSecond, pFrame, pField, pResidual);
        
        animationCurve.addNewKeyFrame(glm::vec2(pFrame,curveKey.GetValue()));
        
        //                cout << "frameRate:"<< frameRate << endl;
        //                cout << "Frame:"<< pFrame << endl;
        //                cout << "Value:"<<curveKey.GetValue() << endl;
    }
    
    animationMap[animationType] = animationCurve;
    
    cout <<animationMap.size() << endl;
//    animationMap[animationType] = animationCurve;
    
}

std::map<CurveAnimationType,AnimationCurve> MeshImporter::importFbxAnimation(FbxScene* scene, FbxNode* node)
{
    std::map<CurveAnimationType,AnimationCurve> animationMap;
    
    int numStacks = scene->GetSrcObjectCount(FbxCriteria::ObjectType(FbxAnimLayer::ClassId));
    for(int j = 0; j < numStacks; j++)
    {
        
        FbxAnimStack* animStackNode = FbxCast<FbxAnimStack>(scene->GetSrcObject(FbxCriteria::ObjectType(FbxAnimStack::ClassId), j));
        
        int numAnimLayers = animStackNode->GetMemberCount(FbxCriteria::ObjectType(FbxAnimLayer::ClassId));
        
        for(int i= 0; i < numAnimLayers; i++)
        {
            FbxAnimLayer* animLayer =
            FbxCast<FbxAnimLayer>(animStackNode->GetMember(FbxCriteria::ObjectType(FbxAnimLayer::ClassId), i));
            
            FbxAnimCurve* animCurve = node->LclTranslation.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_X);
            readFbxAnimationCurve(animationMap, CurveAnimationType::X_MOVE, animCurve);
            

            animCurve = node->LclTranslation.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_Y);
            readFbxAnimationCurve(animationMap, CurveAnimationType::Y_MOVE, animCurve);

            animCurve = node->LclTranslation.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_Z);
            readFbxAnimationCurve(animationMap, CurveAnimationType::Z_MOVE, animCurve);

            
             animCurve = node->LclRotation.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_X);
            readFbxAnimationCurve(animationMap, CurveAnimationType::X_ROTATE, animCurve);

             animCurve = node->LclRotation.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_Y);
            readFbxAnimationCurve(animationMap, CurveAnimationType::Y_ROTATE, animCurve);
            
             animCurve = node->LclRotation.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_Z);
            readFbxAnimationCurve(animationMap, CurveAnimationType::Z_ROTATE, animCurve);

            
            
              animCurve = node->LclScaling.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_X);
            readFbxAnimationCurve(animationMap, CurveAnimationType::X_SCALE, animCurve);
            
              animCurve = node->LclScaling.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_Y);
            readFbxAnimationCurve(animationMap, CurveAnimationType::Y_SCALE, animCurve);
            
              animCurve = node->LclScaling.GetCurve(animLayer, FBXSDK_CURVENODE_COMPONENT_Z);
            readFbxAnimationCurve(animationMap, CurveAnimationType::Z_SCALE, animCurve);
            
            
            
        }
    }
    
    return animationMap;
}


shared_ptr<SkinnedMesh> MeshImporter::importFbxSkinnedMesh(FbxScene* scene,FbxMesh* meshNode)
{
    if(!meshNode)
        return nullptr;
    
    vector<MeshVertex> vertices;
    vector<unsigned short> triangles;
    
    
    unsigned long uPolyCount = meshNode->GetPolygonCount();
    unsigned long uVertexCount = 0;
    //					unsigned long uVertexNumber = 0;
    
    // Dictionary to check if the vertex exists already
    std::map<PackedFBXVertex, unsigned short> vertexMap;
    // Dictionary that maps and original vertex to a list of new vertices that came out of it
    std::map<unsigned short, vector<unsigned short>> originalVertexToNewVertex;
    
    for (int uPoly = 0; uPoly < uPolyCount; ++uPoly)
    {
        // Get number of vertices in current poly - is your mesh triangulated?
        uVertexCount = meshNode->GetPolygonSize((int)uPoly);
        
        for (int uVertex = 0; uVertex < uVertexCount; ++uVertex)
        {
            
            FbxVector4 fbxVertex(0,0,0,0);
            FbxVector4 fbxNormal(0,0,0,0);
            FbxVector2 fbxUV(0,0);
            
            getVertexData(meshNode, uPoly, uVertex, fbxVertex, fbxNormal, fbxUV);
            
            PackedFBXVertex v;
            v.normal = fbxNormal;
            v.position = fbxVertex;
            v.uv = fbxUV;
            
            unsigned short index = 0;
            
            bool found = findVertex(vertexMap, v, index);
            
            if (!found)
            {
                vertices.push_back(MeshVertex(glm::vec3(fbxVertex.mData[0], fbxVertex.mData[1], fbxVertex.mData[2]),glm::vec2(fbxUV.mData[0], fbxUV.mData[1]),glm::vec3(fbxNormal.mData[0], fbxNormal.mData[1], fbxNormal.mData[2])));
                
                unsigned short newIndex = vertices.size() - 1;
                
                vertexMap[v] = newIndex;
                triangles.push_back(newIndex);
                
               	int uVertexIndex = meshNode->GetPolygonVertex(uPoly, uVertex);
                originalVertexToNewVertex[uVertexIndex].push_back(newIndex);
                
            }
            else
            {
                triangles.push_back(index);
                
                int uVertexIndex = meshNode->GetPolygonVertex(uPoly, uVertex);
                originalVertexToNewVertex[uVertexIndex].push_back(index);
                
            }
        }
    }
    
    shared_ptr<SkinnedMesh> skinnedMesh = make_shared<SkinnedMesh>();
    
    skinnedMesh->setVertices(vertices);
    skinnedMesh->setTriangles(triangles);
    
    int deformerCount = meshNode->GetDeformerCount();
    
    vector<glm::mat4> initialPose;
    
    Animation animation;
    
    for(int i = 0 ; i < deformerCount ; i ++)
    {
        FbxDeformer* deformer = meshNode->GetDeformer(i);
        
        if(deformer->GetDeformerType() == FbxDeformer::EDeformerType::eSkin)
        {
            
            
            FbxSkin* skin =  FbxCast<FbxSkin>(deformer);
            
            
            int clusterCount = skin->GetClusterCount();
            
            vector<vector<float>> verticesWeights(vertices.size(),vector<float>(clusterCount));
            
            
            for(int j = 0; j < clusterCount; j++)
            {
                FbxCluster* cluster = skin->GetCluster(j);
                
                
                animation.addAnimationCurveNode(importFbxAnimation(scene,cluster->GetLink()));
                
                FbxAMatrix matrix;
                cluster->GetTransformMatrix(matrix);
                cluster->GetTransformLinkMatrix(matrix);
                
                glm::mat4 glmMat;
                fbxMat4ToglmMat4(matrix, glmMat);
                
                initialPose.push_back(glmMat);
                
                int* controlPoints = cluster->GetControlPointIndices();
                double *weights = cluster->GetControlPointWeights();
                for(int clusterIndex = 0; clusterIndex < cluster->GetControlPointIndicesCount(); clusterIndex++)
                {
                    for(auto &x:  originalVertexToNewVertex[controlPoints[clusterIndex]])
                    {
                        verticesWeights.at(x).at(j) = weights[clusterIndex];
                        
                    }
                    
                    
//                    cout << cluster->GetLink()->GetNameOnly()<< " bone: " << j << " Vertex: " <<controlPoints[clusterIndex] << " weight: " << weights[clusterIndex] << endl;
                    
                }
                
            }
            
            skinnedMesh->setVerticesWeight(verticesWeights);
        }
    }
    skinnedMesh->setInitialPosition(initialPose);
    skinnedMesh->setAnimation(animation);
    
    skinnedMesh->createBuffers();
    

    
    
	return skinnedMesh;
}



shared_ptr<Mesh> MeshImporter::importFbxMesh(string filename)
{
    cout << "filename" << filename << endl;
    
    //	string lFilename = CommonData(filename);
    
	// Initialize the importer.
	bool lImportStatus = lImporter->Initialize(filename.c_str(), -1, fbxManager->GetIOSettings());
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
    
	shared_ptr<Mesh> mesh;
	if (pNode)
	{
		for (int nNode = 0; nNode < pNode->GetChildCount(); nNode++)
		{
			FbxNode* pChildNode = pNode->GetChild(nNode);
            
            FbxNodeAttribute::EType nodeType = pChildNode->GetNodeAttribute() -> GetAttributeType();
            
            switch (nodeType) {
                case FbxNodeAttribute::eMesh:
                {
                    FbxMesh* meshNode =  FbxCast<FbxMesh>(pChildNode->GetNodeAttribute());
                    
                    bool isSkinned = isMeshSkinned(meshNode);
                    if(isSkinned)
                        mesh = importFbxSkinnedMesh(lScene,meshNode);
                    
                    else
                        mesh = importFbxMesh(lScene,meshNode);
                    break;
                }
                    
                    //                case FbxNodeAttribute::eSkeleton:
                    //                {
                    //                    FbxSkeleton* skeletonNode = (FbxSkeleton*)pChildNode->GetNodeAttribute();
                    //                    importFbxSkeleton(skeletonNode);
                    //                    break;
                    //                }
                    
                default:
                    break;
            }
            
            
		}
	}
    //	mesh->createBuffers();
    
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
    
    
	bool loaded = loadOBJ(filename.c_str(), out_vertices, out_uvs, out_normals);
    
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
            
			unsigned short newIndex = mesh->getVerticesCount() - 1;
            
			vertexMap[v] = newIndex;
			mesh->addTriangle(newIndex);
		}
		else
		{
			mesh->addTriangle(index);
		}
	}
    
	mesh->createBuffers();
    
	return mesh;
}