#version 400
in vec3 vertexPosition_modelspace;
void main(){
    gl_Position = vec4(vertexPosition_modelspace,1);

}