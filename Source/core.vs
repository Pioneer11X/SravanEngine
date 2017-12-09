#version 430 core
layout (location = 0) in vec3 pos;	// Attrib 0
layout (location = 1) in vec3 colour;	// Attrib 1
layout (location = 2) in vec2 uv;	// Attrib 2

out vec3 vertexColour;
out vec2 vertexUv;

uniform mat4 transform;

void main(){
	
	gl_Position = transform * vec4(pos, 1.0);
	vertexColour = colour;
	vertexUv = uv;

}