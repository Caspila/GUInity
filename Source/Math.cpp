//#include "Math.hpp"

#include "MathStructs.hpp"

#include <glm/common.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/common.hpp>
#include <glm/gtx/transform.hpp>
#include "print.hpp"
#include <iostream>


//float Math::Deg2Radian = 0.0174532925f;
//float Math::Radian2Deg = 57.2957795f;
//
//
//// Code from http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/
//
//glm::quat Math::RotationBetweenVectors(glm::vec3 start, glm::vec3 dest){
//	start = normalize(start);
//	dest = normalize(dest);
//
//	float cosTheta = dot(start, dest);
//	glm::vec3 rotationAxis;
//
//
//	if (cosTheta < -1 + 0.001f){
//		// special case when vectors in opposite directions:
//		// there is no "ideal" rotation axis
//		// So guess one; any will do as long as it's perpendicular to start
//		rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
//		if (glm::length2(rotationAxis) < 0.01) // bad luck, they were parallel, try again!
//			rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);
//
//		rotationAxis = normalize(rotationAxis);
//		return glm::angleAxis(180.0f, rotationAxis);
//	}
//
//	rotationAxis = cross(start, dest);
//
//	float s = sqrt((1 + cosTheta) * 2);
//	float invs = 1 / s;
//
//	return glm::quat(
//		s * 0.5f,
//		rotationAxis.x * invs,
//		rotationAxis.y * invs,
//		rotationAxis.z * invs
//		);
//
//}
//
//glm::quat Math::LookAt(glm::vec3 direction){
//	// Find the rotation between the front of the object (that we assume towards +Z, 
//	// but this depends on your model) and the desired direction 
//	return RotationBetweenVectors(glm::vec3(0.0f, 0.0f, 1.0f), direction);
//}
//
//glm::quat Math::LookAt(glm::vec3 direction, glm::vec3 desiredUp){
//	// Find the rotation between the front of the object (that we assume towards +Z, 
//	// but this depends on your model) and the desired direction 
//	glm::quat rot1 = RotationBetweenVectors(glm::vec3(0.0f, 0.0f, 1.0f), direction);
//
//	// Recompute desiredUp so that it's perpendicular to the direction
//	// You can skip that part if you really want to force desiredUp
//	glm::vec3 right = glm::cross(direction, desiredUp);
//	desiredUp = glm::cross(right, direction);
//
//	// Because of the 1rst rotation, the up is probably completely screwed up. 
//	// Find the rotation between the "up" of the rotated object, and the desired up
//	glm::vec3 newUp = rot1 * glm::vec3(0.0f, 1.0f, 0.0f);
//	glm::quat rot2 = RotationBetweenVectors(newUp, desiredUp);
//
//	glm::quat targetOrientation = rot2 * rot1; // remember, in reverse orde
//
//	return targetOrientation;
//}
//
//glm::vec3 Math::projectOnPlane(glm::vec3 vector, Plane p)
//{
//	return vector - p.normal * glm::dot(vector, p.normal);
//}
//
//bool Math::CCW(glm::vec3& p1, glm::vec3& p2, glm::vec3& p3)
//{
//    return (p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x) < 0;
//}
//
//void Math::orderVertexCCW(glm::vec3& p1, glm::vec3& p2, glm::vec3& p3)
//{
//    if(CCW(p1,p2,p3))
//        return;
//    else
//    {
//        glm::vec3 aux = p1;
//        
//        p1 = p3;
//        p3 = aux;
//    }
//    
//}
#include "Math.hpp"
#include <glm/common.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/common.hpp>
#include <stack>


//float Deg2Radian = 0.0174532925f;
//float Radian2Deg = 57.2957795f;


// Code from http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/

glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest){
	start = normalize(start);
	dest = normalize(dest);
    
	float cosTheta = dot(start, dest);
	glm::vec3 rotationAxis;
    
    
	if (cosTheta < -1 + 0.001f){
		// special case when vectors in opposite directions:
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
		if (glm::length2(rotationAxis) < 0.01) // bad luck, they were parallel, try again!
			rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);
        
		rotationAxis = normalize(rotationAxis);
		return glm::angleAxis(180.0f, rotationAxis);
	}
    
	rotationAxis = cross(start, dest);
    
	float s = sqrt((1 + cosTheta) * 2);
	float invs = 1 / s;
    
	return glm::quat(
                     s * 0.5f,
                     rotationAxis.x * invs,
                     rotationAxis.y * invs,
                     rotationAxis.z * invs
                     );
    
}

glm::quat LookAt(glm::vec3 direction){
	// Find the rotation between the front of the object (that we assume towards +Z,
	// but this depends on your model) and the desired direction
	return RotationBetweenVectors(glm::vec3(0.0f, 0.0f, 1.0f), direction);
}

glm::quat LookAt(glm::vec3 direction, glm::vec3 desiredUp){
	// Find the rotation between the front of the object (that we assume towards +Z,
	// but this depends on your model) and the desired direction
	glm::quat rot1 = RotationBetweenVectors(glm::vec3(0.0f, 0.0f, 1.0f), direction);
    
	// Recompute desiredUp so that it's perpendicular to the direction
	// You can skip that part if you really want to force desiredUp
	glm::vec3 right = glm::cross(direction, desiredUp);
	desiredUp = glm::cross(right, direction);
    
	// Because of the 1rst rotation, the up is probably completely screwed up.
	// Find the rotation between the "up" of the rotated object, and the desired up
	glm::vec3 newUp = rot1 * glm::vec3(0.0f, 1.0f, 0.0f);
	glm::quat rot2 = RotationBetweenVectors(newUp, desiredUp);
    
	glm::quat targetOrientation = rot2 * rot1; // remember, in reverse orde
    
	return targetOrientation;
}

glm::vec3 projectOnPlane(glm::vec3 vector, Plane p)
{
	return vector - p.normal * glm::dot(vector, p.normal);
}

//bool CCW(glm::vec3& p1, glm::vec3& p2, glm::vec3& p3)
//{
//    return (p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x) > 0;
//}
//
//void orderVertexCCW(glm::vec3& p1, int& i1, glm::vec3& p2, int& i2, glm::vec3& p3, int& i3)
//{
//    if(!CCW(p1,p2,p3))
//    {
//        swap(p1,p3);
//        swap(i1,i3);
//    }
//}
//void orderVertexCCW(glm::vec3& p1, glm::vec3& p2, glm::vec3& p3)
//{
//    if(!CCW(p1,p2,p3))
//        swap(p1,p3);
//}

void orderVertexCCW(glm::vec3& p1, glm::vec3& p2, glm::vec3& p3,glm::vec3& POV)
{
    if(!CCW(p1,p2,p3,POV))
        swap(p1,p3);
}

void orderVertexCCW(glm::vec3& p1, int& i1, glm::vec3& p2, int& i2, glm::vec3& p3, int& i3, glm::vec3 POV)
{
    if(!CCW(p1,p2,p3,POV))
    {
        swap(p1,p3);
        swap(i1,i3);
    }
}

glm::mat4 getPOVMat(glm::vec3& p1, glm::vec3& p2, glm::vec3& p3, const glm::vec3& POV)
{
    glm::mat4 result = {p1.x,p1.y,p1.z,1,
        p2.x,p2.y,p2.z,1,
        p3.x,p3.y,p3.z,1,
        POV.x,POV.y,POV.z,1};
    
    return result;
}

//http://mathforum.org/library/drmath/view/55343.html
bool CCW(glm::vec3& p1, glm::vec3& p2, glm::vec3& p3, const glm::vec3& POV)
{
    return glm::determinant(getPOVMat(p1, p2, p3, POV)) > 0;
}

bool isPlaneFacingPoint(const Plane& p,const glm::vec3& vector)
{
    //glm::vec3 dir = vector - p.point;
    
    return glm::dot(p.normal, vector - p.point) > 0;
}

float distanceVertexPlane(glm::vec3 vertex, Plane p)
{
    //glm::vec3 vertex = vertices[vertexIndex];
    
    glm::vec3 projectedVertex = projectOnPlane(vertex, p);
    
    return glm::distance(projectedVertex, vertex);
}


//
//struct MeshTriangle
//{
//public:
//    Plane p;
//    int i1, i2, i3;
//    
//    bool deleted;
//    
//    MeshTriangle(int i1, int i2, int i3, Plane p)
//    {
//        this->i1 = i1;
//        this->i2 = i2;
//        this->i3 = i3;
//        
//        this->p = p;
//        
//        deleted = false;
//    }
//    bool getFurthestPoint(vector<glm::vec3> vertices, glm::vec3& furthest, int& furthestIndex)
//    {
//        if(frontFacingPoints.empty())
//            return false;
//
//        int maxIndex = frontFacingPoints[0];
//        float maxDistance = distanceVertexPlane(vertices[maxIndex],p);;
//
//        
//        
//        //int i = 1;
//        //for(auto&vertexIndex : frontFacingPoints)
//        for(int i = 1; i < frontFacingPoints.size(); i++)
//        {
//            int vertexIndex = frontFacingPoints[i];
//           float distance = distanceVertexPlane(vertices[vertexIndex],p);
//            
//            if(distance > maxDistance)
//            {
//                maxDistance = distance;
//                maxIndex = vertexIndex;
//            }
//            
//            //i++;
//        }
//
//        furthest = vertices[maxIndex];
//        furthestIndex = maxIndex;
//        return true;
//    }
//    
//    vector<weak_ptr<MeshTriangle>> getAdjacentFacingTriangles(glm::vec3 point)
//    {
//        vector<weak_ptr<MeshTriangle>> adjacentFacingPoint;
//        
//        for(auto& triangleUnlock : adjacentFaces)
//        {
//            shared_ptr<MeshTriangle> currentTriangle = triangleUnlock.lock();
//            
//            if(currentTriangle)
//            {
//                if(isPlaneFacingPoint(currentTriangle->p, point))
//                    adjacentFacingPoint.push_back(triangleUnlock);
//            }
//        }
//        
//        return adjacentFacingPoint;
//        
//    }
//    
//    vector<int> frontFacingPoints;
//    vector<weak_ptr<MeshTriangle>> adjacentFaces;
//};
//
//struct MeshTriangleEdge
//{
//public:
//    int i1, i2;
//    weak_ptr<MeshTriangle> triangle;
//    
//    MeshTriangleEdge(int i1, int i2, weak_ptr<MeshTriangle> triangle)
//    {
//        this->i1 = i1;
//        this->i2 = i2;
//        this->triangle = triangle;
//    }
//};
//
//MeshTriangle createMeshTriangleNonPTR(vector<glm::vec3> vertices, int i1, int i2, int i3, glm::vec3 normalRef)
//{
//    glm::vec3 p1,p2,p3;
//    p1 = vertices[i1];
//    p2 = vertices[i2];
//    p3 = vertices[i3];
//    
//    glm::vec3 center = (p1+p2+p3) * (1.0f/3);
//    //
//    //    |x1 y1 z1 1|
//    //    |x2 y2 z2 1|
//    //    d = |x3 y3 z3 1|.
//    //    |x4 y4 z4 1|
//    
//    //orderVertexCCW(p1,i1,p2,i2,p3,i3);
//    Plane p(p1,p2,p3,center);
//    //p.normal = center - normalRef;
//    
//    return MeshTriangle(i1,i2,i3,p);
//}
//
//shared_ptr<MeshTriangle> createMeshTriangle(vector<glm::vec3> vertices, int i1, int i2, int i3, glm::vec3 normalRef)
//{
//    
//                                    cout<< "V Created triangle: " << i1 << "," << i2 << "," << i3 << endl;
//    
//    glm::vec3 p1,p2,p3;
//    p1 = vertices[i1];
//    p2 = vertices[i2];
//    p3 = vertices[i3];
//    
//    //glm::vec3 center = (p1+p2+p3) * (1.0f/3);
////    
////    |x1 y1 z1 1|
////    |x2 y2 z2 1|
////    d = |x3 y3 z3 1|.
////    |x4 y4 z4 1|
//    
//    orderVertexCCW(p1,i1,p2,i2,p3,i3,normalRef);
//    Plane p(p1,p2,p3,normalRef);
//    //p.normal = center - normalRef;
//    
//    return make_shared<MeshTriangle>(i1,i2,i3,p);
//}
//
//void assignPointsToFaceFromSubset(vector<glm::vec3>& vertices,vector<int> subset, shared_ptr<MeshTriangle> face)
//{
//
//    for(int i = 0; i < subset.size(); i++)
//    {
//        int vertexIndex = subset[i];
////        glm::vec3 currentVertex = vertices[i];
////        
////    
////    for(auto&vertexIndex : subset)
////    {
//        glm::vec3 currentVertex = vertices[vertexIndex];
//        
//        if(face->i1 == vertexIndex || face->i2 == vertexIndex || face->i3 == vertexIndex)
//            continue;
//        
//        if(isPlaneFacingPoint(face->p, currentVertex))
//            face->frontFacingPoints.push_back(vertexIndex);
//        
//    }
//}
//
//void assignPointsToFace(vector<glm::vec3>& vertices,shared_ptr<MeshTriangle> face)
//{
////    int i = 0;
////    for(auto&currentVertex : vertices)
//    cout <<"Normal: "<< face->p.normal << endl;
//    for(int i = 0; i < vertices.size(); i++)
//    {
//        glm::vec3 currentVertex = vertices[i];
//        if(face->i1 == i || face->i2 == i || face->i3 == i)
//            continue;
//        
//        if(isPlaneFacingPoint(face->p, currentVertex))
//            face->frontFacingPoints.push_back(i);
//        
//  //      i++;
//    }
//}
//
//bool isSharedEdge(int i1, int i2, shared_ptr<MeshTriangle> triangle, int& edge)
//{
//    edge = -1;
//    if  (i1 == triangle->i1 && i2 == triangle->i2)
//       edge = 0;
//        if(i1 == triangle->i2 && i2 == triangle->i3)
//       edge = 1;
//       if (i1 == triangle->i3 && i2 == triangle->i1)
//        edge = 2;
//
//    
//    if   (i1 == triangle->i2 && i2 == triangle->i1)
//       edge = 0;
//       if(i1 == triangle->i3 && i2 == triangle->i2)
//       edge = 1;
//       if(i1 == triangle->i1 && i2 == triangle->i3)
//        edge = 2;
//
//    
//    return edge >=0;
//}
//
//
//bool isSharedEdge(int i1, int i2, shared_ptr<MeshTriangle> triangle)
//{
//    int edge = 0;
//    return isSharedEdge(i1,i2,triangle,edge);
////    
////    if ( (i1 == triangle->i1 && i2 == triangle->i2)
////        
////    ||(i1 == triangle->i2 && i2 == triangle->i3)
////      
////    || (i1 == triangle->i3 && i2 == triangle->i1))
////        return true;
////      
////    
////    
////    if(   (i1 == triangle->i2 && i2 == triangle->i1)
////
////||(i1 == triangle->i3 && i2 == triangle->i2)
////
////  ||(i1 == triangle->i1 && i2 == triangle->i3))
////        return true;
////    
////    
////    
////    return false;
//}
//
//vector<MeshTriangleEdge> getNonSharedEdges(vector<weak_ptr<MeshTriangle>> adjacentTriangles,shared_ptr<MeshTriangle> triangle)
//{
// 
//    vector<MeshTriangleEdge> result;
// 
//    bool i1i2shared, i2i3shared,i3i1shared;
//    i1i2shared= i2i3shared=i3i1shared = false;
//    
//    for(auto& adjacentUnlock : adjacentTriangles)
//    {
//        shared_ptr<MeshTriangle> adjacent = adjacentUnlock.lock();
//        
//        if(!adjacent)
//            continue;
//        
//        
//        //if(!isSharedEdge(triangle->i1, triangle->i2, adjacent))
//        int edge = 0;
//        if(!isSharedEdge(adjacent->i1, adjacent->i2, triangle,edge))
//        {
//
//            result.push_back(MeshTriangleEdge(adjacent->i1,adjacent->i2,adjacent));
//
//        }
//        if(edge == 0)
//            i1i2shared = true;
//        if(edge == 1)
//            i2i3shared = true;
//        if(edge == 2)
//            i3i1shared = true;
//        if(!isSharedEdge(adjacent->i2, adjacent->i3, triangle,edge))
//        {
//
//            result.push_back(MeshTriangleEdge(adjacent->i2,adjacent->i3,adjacent));
//        }
//        if(edge == 0)
//            i1i2shared = true;
//        if(edge == 1)
//            i2i3shared = true;
//        if(edge == 2)
//            i3i1shared = true;
//        if(!isSharedEdge(adjacent->i3, adjacent->i1, triangle,edge))
//        {
//
//            result.push_back(MeshTriangleEdge(adjacent->i3,adjacent->i1,adjacent));
//        }
//        if(edge == 0)
//            i1i2shared = true;
//        if(edge == 1)
//            i2i3shared = true;
//        if(edge == 2)
//            i3i1shared = true;
//    
//    
//    }
//    if(!i1i2shared)
//    result.push_back(MeshTriangleEdge(triangle->i1,triangle->i2,triangle));
//    if(!i2i3shared)
//    result.push_back(MeshTriangleEdge(triangle->i2,triangle->i3,triangle));
//    if(!i3i1shared)
//    result.push_back(MeshTriangleEdge(triangle->i3,triangle->i1,triangle));
//    
//    return result;
//}
//
////vector<MeshTriangleEdge> getNonSharedEdges(vector<weak_ptr<MeshTriangle>> adjacentTriangles,shared_ptr<MeshTriangle> triangle)
////{
////    
////    vector<MeshTriangleEdge> result;
////    
////    bool i1i2shared, i2i3shared,i3i1shared;
////    i1i2shared= i2i3shared=i3i1shared = false;
////    
////    for(auto& adjacentUnlock : adjacentTriangles)
////    {
////        shared_ptr<MeshTriangle> adjacent = adjacentUnlock.lock();
////        
////        if(!adjacent)
////            continue;
////        
////        
////        //if(!isSharedEdge(triangle->i1, triangle->i2, adjacent))
////        if(!isSharedEdge(adjacent->i1, adjacent->i2, triangle))
////        {
////            i1i2shared = true;
////            result.push_back(MeshTriangleEdge(adjacent->i1,adjacent->i2,adjacent));
////            
////        }
////
////        if(!isSharedEdge(adjacent->i2, adjacent->i3, triangle))
////        {
////            i2i3shared = true;
////            result.push_back(MeshTriangleEdge(adjacent->i2,adjacent->i3,adjacent));
////        }
////
////        if(!isSharedEdge(adjacent->i3, adjacent->i1, triangle))
////        {
////            i3i1shared = true;
////            result.push_back(MeshTriangleEdge(adjacent->i3,adjacent->i1,adjacent));
////        }
////
////        
////        
////    }
////    if(!i1i2shared)
////        result.push_back(MeshTriangleEdge(triangle->i1,triangle->i2,triangle));
////    if(!i2i3shared)
////        result.push_back(MeshTriangleEdge(triangle->i2,triangle->i3,triangle));
////    if(!i3i1shared)
////        result.push_back(MeshTriangleEdge(triangle->i3,triangle->i1,triangle));
////    
////    return result;
////}
//
//template<typename T, typename X>
//bool contains(T container,X element)
//{
//    if(find(container.begin(),container.end(),element) == container.end())
//        return false;
//    
//    return true;
//}
//
//
//glm::vec3 getCenterFor(vector<glm::vec3> vertices, vector<MeshTriangleEdge> edges)
//{
//    glm::vec3 avg;
//    for(auto&x : edges)
//    {
//        avg += vertices[x.i1];
//    }
//    
//    avg = avg * (1.0f/edges.size());
//    
//    return avg;
//}
//
//bool isSameTriangle(int i1, int i2, int i3, shared_ptr<MeshTriangle> tri)
//{
//    int cont = 0;
//    if(i1 == tri->i1 || i1 == tri->i2 || i1 == tri->i3)
//        cont++;
//    if(i2 == tri->i1 || i2 == tri->i2 || i2 == tri->i3)
//        cont++;
//    if(i3 == tri->i1 || i3 == tri->i2 || i3 == tri->i3)
//        cont++;
//
//    return cont==3;
//}
//
//bool meshTriangleExists(vector<shared_ptr<MeshTriangle>> faces, int i1,int i2,int i3)
//{
////    orderVertexCCW(vertices[i1], i1, vertices[i2], i2, vertices[i3], i3, POV)
//    
//    for (shared_ptr<MeshTriangle> meshTriangle : faces) {
//        if(isSameTriangle(i1, i2, i3, meshTriangle))
//           return true;
//    }
//           
//           return false;
//}
//
//void getMaxDistance(vector<glm::vec3> vertices, int minMaxEP[], int& i1, int& i2)
//{
//    int i1Temp, i2Temp;
//    i1Temp = 0; i2Temp = 0;
//    float maxDistance;
//    maxDistance = 0;
//    
//    for(int i = 0; i < 6; i++)
//    {
//        for(int j = 0; j < 6; j++)
//        {
//            if(i==j)
//                continue;
//            
//            float distance = glm::distance(vertices[minMaxEP[i]], vertices[minMaxEP[j]]) ;
//            if(distance > maxDistance)
//            {
//                i1Temp = i;
//                i2Temp = j;
//                maxDistance = distance;
//            }
//        }
//    }
//    
//    i1 = i1Temp;
//    i2 = i2Temp;
//}
//
//float distanceLinePoint(glm::vec3 v, glm::vec3 w, glm::vec3 p)
//{
//    // Return minimum distance between line segment vw and point p
//    const float l2 = glm::length(w-v) * glm::length(w-v);  // i.e. |w-v|^2 -  avoid a sqrt
//    if (l2 == 0.0) return distance(p, v);   // v == w case
//    // Consider the line extending the segment, parameterized as v + t (w - v).
//    // We find projection of point p onto the line.
//    // It falls where t = [(p-v) . (w-v)] / |w-v|^2
//    const float t = glm::dot(p - v, w - v) / l2;
//    if (t < 0.0) return distance(p, v);       // Beyond the 'v' end of the segment
//    else if (t > 1.0) return distance(p, w);  // Beyond the 'w' end of the segment
//    const glm::vec3 projection = v + t * (w - v);  // Projection falls on the segment
//    return glm::distance(p, projection);
//}
//
//int getFarFromBase(vector<glm::vec3>vertices,int minMaxEPi[],int baseI1,int baseI2)
//{
//    glm::vec3 baseP1, baseP2;
//    baseP1 = vertices[baseI1];
//    baseP2 = vertices[baseI2];
//
//    int baseI3 = 0;
//    
//    float maxDistance = 0;
//
//    for(int i = 0; i < 6; i ++)
//    {
//        if(i == minMaxEPi[i])
//            continue;
//        
//        int currentI = minMaxEPi[i];
//        glm::vec3 currentP = vertices[currentI];
//        
//        float distance = distanceLinePoint(baseP1,baseP2,currentP);
//        if(distance > maxDistance)
//        {
//            maxDistance = distance;
//            baseI3 = currentI;
//        }
//    }
//    
//    return baseI3;
//}
//
//int getFarthestFromPlane(vector<glm::vec3> vertices, Plane& p)
//{
//    int maxIndex = 0;
//    float maxDistance = 0;
//    
//    for(int i= 0; i < vertices.size(); i++)
//    {
//        float distance = distanceVertexPlane(vertices[i], p);
//        if(distance > maxDistance)
//        {
//            maxDistance = distance;
//            maxIndex = i;
//        }
//    }
//    
//    return maxIndex;
//}
//
//void getInitialTetrahedron(vector<glm::vec3> vertices, int& i1, int& i2, int& i3, int& i4)
//{
//    glm::vec3 minMaxEP[6]; //min x,y,z / max x,y,z
//    int minMaxEPi[6];
//    //int minXi, minYi, minZi, maxXi, maxYi,maxZi;
//    minMaxEPi[0] = minMaxEPi[1] = minMaxEPi[2] = minMaxEPi[3] = minMaxEPi[4] = minMaxEPi[5] = 0;
//    //minXi = minYi = minZi = maxXi = maxYi = maxZi = 0;
//
//    minMaxEP[0] = vertices[minMaxEPi[0]];
//    minMaxEP[1] = vertices[minMaxEPi[1]];
//    minMaxEP[2] = vertices[minMaxEPi[2]];
//    minMaxEP[3] = vertices[minMaxEPi[3]];
//    minMaxEP[4] = vertices[minMaxEPi[4]];
//    minMaxEP[5] = vertices[minMaxEPi[5]];
//    
//    for(int i= 1; i < vertices.size(); i++)
//    {
//        glm::vec3& vertex = minMaxEP[i];
//        
//        if(vertex.x < minMaxEP[0].x )
//        {
//            minMaxEP[0] = vertex;
//            minMaxEPi[0] =i;
//        }
//        if(vertex.y < minMaxEP[1].y)
//        {
//            minMaxEP[1] = vertex;
//            minMaxEPi[1] =i;
//        }
//        if(vertex.z < minMaxEP[2].z)
//        {
//            minMaxEP[2] = vertex;
//            minMaxEPi[2] =i;
//        }
//        if(vertex.x > minMaxEP[3].x)
//        {
//            minMaxEP[3] = vertex;
//            minMaxEPi[3] =i;
//        }
//        if(vertex.y > minMaxEP[4].y)
//        {
//            minMaxEP[4] = vertex;
//            minMaxEPi[4] =i;
//        }
//        if(vertex.z > minMaxEP[5].z)
//        {
//            minMaxEP[5] = vertex;
//            minMaxEPi[5] =i;
//        }
//    }
//    
//    int baseI1, baseI2;
//    getMaxDistance(vertices,minMaxEPi, baseI1, baseI2);
//    
//    int baseI3;
//    baseI3 = getFarFromBase(vertices,minMaxEPi,baseI1,baseI2);
//    
//    Plane plane1(vertices[baseI1],vertices[baseI3],vertices[baseI2]);
//    Plane plane2(vertices[baseI2],vertices[baseI3],vertices[baseI1]);
//
//    int far1, far2;
//    far1 = getFarthestFromPlane(vertices,plane1);
//    far2 = getFarthestFromPlane(vertices,plane2);
//    
//    int baseI4;
//    float distFar1, distFar2;
//    distFar1 = distanceVertexPlane(vertices[far1], plane1);
//    distFar2 = distanceVertexPlane(vertices[far2], plane2);
//    
//    if(distFar1 > distFar2)
//        baseI4 = far1;
//    else
//        baseI4 = far2;
//    
//    i1 = baseI1;
//        i2 = baseI2;
//        i3 = baseI3;
//        i4 = baseI4;
//    
//}
//
//void adjustAdjacent(vector<weak_ptr<MeshTriangle>> newFaces)
//{
//    for(int i = 0 ; i < newFaces.size(); i++)
//    {
//        shared_ptr<MeshTriangle> faceLock = newFaces[i].lock();
//        if(!faceLock)
//            continue;
//        
//        for(int j = 0; j < newFaces.size(); j++)
//        {
//            if(i == j)
//                continue;
//            
//            shared_ptr<MeshTriangle> faceLock2 = newFaces[j].lock();
//            if(!faceLock2)
//                continue;
//
//            
//            if(isSharedEdge(faceLock->i1, faceLock->i2, faceLock2))
//                faceLock->adjacentFaces.push_back(faceLock2);
//            if(isSharedEdge(faceLock->i2, faceLock->i3, faceLock2))
//                faceLock->adjacentFaces.push_back(faceLock2);
//            if(isSharedEdge(faceLock->i3, faceLock->i1, faceLock2))
//                faceLock->adjacentFaces.push_back(faceLock2);
//
//        }
//    }
//    
//}
//
//vector<weak_ptr<MeshTriangle>> getAdjacent(shared_ptr<MeshTriangle> triangle, vector<weak_ptr<MeshTriangle>> faces)
//{
//    
//    vector<weak_ptr<MeshTriangle>> result;
//    for(auto& adjacentUnlock : faces)
//    {
//        shared_ptr<MeshTriangle> adjacent = adjacentUnlock.lock();
//        
//        if(!adjacent)
//            continue;
//        
//         if(!isSharedEdge(triangle->i1, triangle->i2, adjacent)
//            && !isSharedEdge(triangle->i2, triangle->i3, adjacent)
//            && !isSharedEdge(triangle->i3, triangle->i1, adjacent))
//         {
//             
//         }
//        else
//            result.push_back(adjacentUnlock);
//            
//             
//        
//    }
//    
//    return result;
//}
//
//      vector<int> getAllFacingPoints(vector<weak_ptr<MeshTriangle>>facingTriangles,shared_ptr<MeshTriangle> currentTriangle)
//{
//    vector<int> result;
//    
//    for (int i = 0; i < facingTriangles.size(); i++) {
//        shared_ptr<MeshTriangle> face = facingTriangles[i].lock();
//        if(!face)
//            continue;
//        
//        for (int j = 0; j < face->frontFacingPoints.size(); j++) {
//            result.push_back(face->frontFacingPoints[j]);
//        }
//        
//        //face->frontFacingPoints.clear();
//    }
//    
//    for (int j = 0; j < currentTriangle->frontFacingPoints.size(); j++) {
//        result.push_back(currentTriangle->frontFacingPoints[j]);
//        
//        //currentTriangle->frontFacingPoints.clear();
//    }
//    
//    return result;
//}
//
//void convexHull(vector<glm::vec3>& vertices, vector<int>& usedIndex, vector<int>& triangles)
//{
//    
//    
//    vector<shared_ptr<MeshTriangle>> faces;
//    stack<weak_ptr<MeshTriangle>> faceStack;
//    bool* verticeAssigned = new bool[vertices.size()];
//    
//    for(int i = 0; i < vertices.size();i++)
//    {
//        verticeAssigned[i] = false;
//    }
//    
//    {
//        int i1,i2,i3,i4;
//        getInitialTetrahedron(vertices, i1, i2, i3, i4);
//        
//        //i1 = 0; i2 = 1; i3 = 2; i4 = 4;
//        
//
//        
//    //TODO, find the extreme points for a better starting point
//    glm::vec3 p1,p2,p3,p4, center;
//    p1 = vertices[i1];
//    p2 = vertices[i2];
//    p3 = vertices[i3];
//    p4 = vertices[i4];
//        
//    center = (p1+p2+p3+p4)*(1/4.0f);
//
//        
//        
//    shared_ptr<MeshTriangle> base = createMeshTriangle(vertices, i1,i2,i3,center);
//    shared_ptr<MeshTriangle> tri1 = createMeshTriangle(vertices, i1,i2,i4,center);
//    shared_ptr<MeshTriangle> tri2 = createMeshTriangle(vertices, i2,i3,i4,center);
//    shared_ptr<MeshTriangle> tri3 = createMeshTriangle(vertices, i3,i1,i4,center);
//
//        faces.push_back(base); //0
//        faces.push_back(tri1); //1
//        faces.push_back(tri2); //2
//        faces.push_back(tri3); //3
//        
//        for(int faceI = 0; faceI < faces.size(); faceI++)
//        {
//            shared_ptr<MeshTriangle> face = faces[faceI];
//            
//            for (int pointI=0; pointI < vertices.size(); pointI++) {
//                if(verticeAssigned[pointI])
//                    continue;
//                
//                if(isPlaneFacingPoint(face->p, vertices[pointI]))
//                {
//                    face->frontFacingPoints.push_back(pointI);
//                    verticeAssigned[pointI] = true;
//                }
//            }
//            
//        }
//        
//        
//        
////    assignPointsToFace(vertices,base);
////    assignPointsToFace(vertices,tri1);
////    assignPointsToFace(vertices,tri2);
////    assignPointsToFace(vertices,tri3);
//    
//    base->adjacentFaces = {tri1,tri2,tri3};
//    tri1->adjacentFaces = {base,tri2,tri3};
//    tri2->adjacentFaces = {tri1,base,tri3};
//    tri3->adjacentFaces = {tri1,tri2,base};
//
//
//        
//    faceStack.push(base);
//    faceStack.push(tri1);
//    faceStack.push(tri2);
//    faceStack.push(tri3);
//    }
//    
//
//    
//    while(!faceStack.empty())
//    {
//        cout <<faceStack.size() << " items in the stack."<<endl;
//        
//        shared_ptr<MeshTriangle> currentTriangle = faceStack.top().lock();
//        faceStack.pop();
//        
//        if(!currentTriangle)
//        {
//            continue;
//        }
//        
//        cout<< "X Popped triangle: " << currentTriangle->i1 << "," << currentTriangle->i2 << "," << currentTriangle->i3 << endl;
//        
//
//        int farPointIndex;
//        glm::vec3 farPoint;
//        bool hasFurthest = currentTriangle->getFurthestPoint(vertices,farPoint, farPointIndex);
//        
//        if(!hasFurthest)
//            continue;
//        
//        vector<weak_ptr<MeshTriangle>> facingTriangles = currentTriangle->getAdjacentFacingTriangles(farPoint);
//        
//
//        
//        vector<MeshTriangleEdge> edges = getNonSharedEdges(facingTriangles,currentTriangle);
//
//        vector<int> allFacingPoints = getAllFacingPoints(facingTriangles,currentTriangle);
//        
//        for(int i = 0; i < allFacingPoints.size(); i++)
//        {
//            verticeAssigned[allFacingPoints[i]] = false;
//        }
//        
//        glm::vec3 newCenter = getCenterFor(vertices,edges);
//        
//        //if(edges.empty())
//        //{
//        //    cout << "Weird, edges should not be empty" << endl;
//        //    continue;
//        //}
//
//        
//        vector<weak_ptr<MeshTriangle>> newFaces;
//        
//        for(int i = 0; i < edges.size(); i++)
//        {
//            int i1 = edges[i].i1;
//            int i2 = edges[i].i2;
//
////            MeshTriangle
////            
//            if (meshTriangleExists(faces,i1,i2,farPointIndex)) {
//                continue;
//            }
//            
//            shared_ptr<MeshTriangle> newTriangle = createMeshTriangle(vertices, farPointIndex,i1,i2,newCenter);
//
//            //assignPointsToFaceFromSubset(vertices,currentTriangle->frontFacingPoints,newTriangle);
//            
////            assignPointsToFace(vertices,newTriangle);
//            
//            
//            shared_ptr<MeshTriangle> oldTriangle = edges[i].triangle.lock();
//            
//            if(oldTriangle)
//            {
//            newTriangle->adjacentFaces = getAdjacent(newTriangle,oldTriangle->adjacentFaces);
//            for(auto& x : newTriangle->adjacentFaces)
//            {
//                if(x.lock())
//                    x.lock()->adjacentFaces.push_back(newTriangle);
//            }
//            }
//            
//
//
//            faces.push_back(newTriangle);
//            faceStack.push(newTriangle);
//            
//            newFaces.push_back(newTriangle);
//        }
//
//        for(int i = 0; i < facingTriangles.size(); i++)
//        {
//            shared_ptr<MeshTriangle> meshTri = facingTriangles[i].lock();
//            
//            if(meshTri)
//                if(contains(faces, meshTri))
//                {
//                    faces.erase(find(faces.begin(),faces.end(),meshTri));
//                    cout<< "X Deleted triangle: " << meshTri->i1 << "," << meshTri->i2 << "," << meshTri->i3 << endl;
//                }
//        }
//        if(contains(faces, currentTriangle))
//        {
//            faces.erase(find(faces.begin(),faces.end(),currentTriangle));
//            
//            cout<< "X Deleted triangle: " << currentTriangle->i1 << "," << currentTriangle->i2 << "," << currentTriangle->i3 << endl;
//        }
//        
//        adjustAdjacent(newFaces);
//
//        for(int faceI = 0; faceI < newFaces.size(); faceI++)
//        {
//            shared_ptr<MeshTriangle> face = newFaces[faceI].lock();
//
//            if(!face)
//                continue;
//            
//            for (int pointI=0; pointI < allFacingPoints.size(); pointI++) {
//                
//                int index = allFacingPoints[pointI];
//                if(verticeAssigned[index])
//                    continue;
//                
//                if(isPlaneFacingPoint(face->p, vertices[index]))
//                {
//                    face->frontFacingPoints.push_back(index);
//                    verticeAssigned[index] = true;
//                }
//            }
//            
//        }
//        for(int faceI = 0; faceI < newFaces.size(); faceI++)
//        {
//            shared_ptr<MeshTriangle> face = newFaces[faceI].lock();
//            
//            if(!face)
//                continue;
//            
//            cout<< "Adjacents to: " << face->i1 << "," << face->i2 << "," << face->i3 << endl;
//            
//            for (int z = 0; z < face->adjacentFaces.size(); z++) {
//                shared_ptr<MeshTriangle> face2 = face->adjacentFaces[z].lock();
//                
//                if(!face2)
//                    continue;
//                            cout <<"->"<< face2->i1 << "," << face2->i2 << "," << face2->i3 << endl;
//            }
//        }
//        
//    }
//    
//    usedIndex.clear();
//    triangles.clear();
//    for(shared_ptr<MeshTriangle> triangle : faces )
//    {
//        if(triangle == nullptr)
//            continue;
//        
//        if(!contains(usedIndex, triangle->i1))
//           usedIndex.push_back(triangle->i1);
//        
//        if(!contains(usedIndex, triangle->i2))
//           usedIndex.push_back(triangle->i2);
//        
//        if(!contains(usedIndex, triangle->i3))
//           usedIndex.push_back(triangle->i3);
//        
//        triangles.push_back(triangle->i1);
//        triangles.push_back(triangle->i2);
//        triangles.push_back(triangle->i3);
//    }
//    
//    //faces.push(MeshTriangle)
//}
