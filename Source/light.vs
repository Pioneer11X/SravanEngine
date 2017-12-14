#version 430 core

// Shader for the Light Cube.

layout (location = 0) in vec3 pos;	// Attrib 0
layout (location = 1) in vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoords;

void main(){
	
	gl_Position = projection * view * model * vec4(pos, 1.0);
	TexCoords = uv;

}