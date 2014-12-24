#version 400
layout(location=0) in vec3 vert;
layout(location=1) in vec3 vertColor;
layout(location=2) in vec3 vertNormal;

uniform mat4 camera ; // VP = Projection * View
uniform mat4 model ; // model

out vec3 fragVert;
out vec3 fragNormal;
void main(){

    // Pass some variables to the fragment shader
    fragNormal = vertNormal;
    fragVert = vert;
    
    // Apply all matrix transformations to vert
    gl_Position = camera * model * vec4(vert, 1);

}