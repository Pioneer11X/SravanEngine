#version 430 core
layout (location = 0) in vec3 pos;	// Attrib 0
layout (location = 1) in vec2 uv;	// Attrib 1

out vec2 vertexUv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main(){
	
	gl_Position = projection * view * model * vec4(pos, 1.0);
	vertexUv = uv;

}