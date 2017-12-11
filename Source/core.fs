#version 430 core
out vec4 FragColour;

in vec2 vertexUv;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 objectColour;
uniform vec3 lightColour;

void main(){

	// FragColour = vec4(vertexColour, 1.0);
	// FragColour = mix(texture(texture1, vertexUv), texture(texture2, vertexUv), 0.5) * vec4(vertexColour, 1.0);
	// FragColour = texture(texture2, vertexUv);
	FragColour = mix(texture(texture1, vertexUv), texture(texture2, vertexUv), 0.1) * vec4(lightColour * objectColour, 1.0);

}