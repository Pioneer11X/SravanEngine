#version 450 core
layout (location = 0) in vec3 pos;	// Attrib 0

void main(){
	
	gl_Position = vec4(pos, 1.0);

}