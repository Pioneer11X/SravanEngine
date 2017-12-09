#version 450 core
layout (location = 0) in vec3 pos;	// Attrib 0
layout (location = 1) in vec3 colour;	// Attrib 1

out vec3 vertexColour;

void main(){
	
	gl_Position = vec4(pos, 1.0);
	vertexColour = colour;

}