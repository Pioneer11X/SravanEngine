#version 450 core
out vec4 FragColour;

in vec3 vertexColour;

void main(){

	FragColour = vec4(vertexColour, 1.0);

}