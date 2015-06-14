#version 400
layout(location=0) in vec3 vert;
layout(location=1) in vec3 vertColor;
layout(location=2) in vec3 vertNormal;
layout(location=3) in vec2 vertexUV;
layout(location=4) in vec3 boneIndex;
layout(location=5) in vec3 boneWeight;

uniform mat4 camera ; // VP = Projection * View
uniform mat4 model ; // model
uniform mat4 boneTransform[10] ; // current bone pose
uniform int nBones ; // current bone pose


out vec2 UV;
out vec3 fragVert;
out vec3 fragNormal;
void main(){

    // Pass some variables to the fragment shader
    fragNormal = vertNormal;
    fragVert = vert;

	UV = vertexUV;
    

    int index;
    vec4 vert4 = vec4(vert,1);
    vec4 newVertex = vert4;

    //index = int(boneIndex.x);

    if(nBones!=0)
    {
        newVertex = ((boneTransform[int(boneIndex.x)]) * vert4) * boneWeight.x;
      //  ((boneTransform[int(boneIndex.y)]) * boneWeight.y) *
      //  ((boneTransform[int(boneIndex.z)]) * boneWeight.z) * vert4;

      newVertex = ((boneTransform[int(boneIndex.y)]) * vert4) * boneWeight.y + newVertex;
      newVertex = ((boneTransform[int(boneIndex.z)]) * vert4) * boneWeight.z + newVertex;
      //  ((boneTransform[int(boneIndex.y)]) * boneWeight.y) *
      //  ((boneTransform[int(boneIndex.z)]) * boneWeight.z) * vert4;

      newVertex = vert4 + newVertex;
      //vert4 = vert4 + newVertex;
    }
    //newVertex = (boneTransform[index] * vert4) * boneWeight.x;

	//index = int(boneIndex.y);
    //newVertex = (boneTransform[index] * vert4) * boneWeight.y + newVertex;

	//index = int(boneIndex.z);
    //newVertex = (boneTransform[index] * vert4) * boneWeight.z + newVertex;


//    mat4 allBoneWeight = mat4(1);
//    for(int i=0;i<10;i++)
//    {
//    	allBoneWeight = allBoneWeight * boneTransform[i];// * boneWeight[i]);
//    }

    gl_Position = camera * model * vec4(newVertex.xyz,1);//vec4(newVertex.xyz,1);//  * allBoneWeight * vec4(vert, 1);

}