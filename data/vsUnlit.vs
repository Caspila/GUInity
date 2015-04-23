#version 400
layout(location=0) in vec3 vert;
layout(location=1) in vec3 vertColor;
layout(location=2) in vec3 vertNormal;
layout(location=3) in vec2 vertexUV;

uniform mat4 camera ; // VP = Projection * View
uniform mat4 model ; // model

out vec2 UV;
void main(){


	UV = vertexUV;
    
    // Apply all matrix transformations to vert
    gl_Position = camera * model * vec4(vert, 1);

}