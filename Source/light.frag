#version 430
in vec2 TexCoords;

out vec4 FragColour;

uniform sampler2D lightImage;

void main(){
    // FragColour = vec4( ((texture(lightImage, TexCoords)).rgb), 1.0);
	FragColour = texture(lightImage, TexCoords);
}