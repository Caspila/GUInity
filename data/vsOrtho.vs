#version 400

layout(location=0) in vec3 vertexPosition_modelspace;
layout(location=3) in vec2 vertexUV;

uniform mat4 ortho ;
uniform mat4 model ; 

out vec2 UV;

void main(){
    vec4 v = vec4(vertexPosition_modelspace,1);
	
	UV = vertexUV;

	gl_Position = ortho * model * v;

	
}