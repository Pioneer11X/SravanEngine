#version 430

out vec4 FragColour;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct DirectionalLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight{

	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linearConstant;
	float quadraticConstant;

};

struct SpotLight{

	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float cutoff;


};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform Material material;
uniform SpotLight light;  
uniform vec3 viewPos; // This is the Camera Position in World Space.

void main(){

	float distance = length(light.position - FragPos);
	


	// Ambient
	vec3 ambient  = light.ambient * (texture(material.diffuse, TexCoords)).rgb;
	
	
	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float theta = dot(lightDir, normalize(-light.direction));

	vec3 diffuse = vec3(0);
	vec3 specular = vec3(0);

	if ( theta > light.cutoff ){

		float diff = max(dot(norm, lightDir), 0.0);
		diffuse = light.diffuse * diff * ((texture(material.diffuse, TexCoords)).rgb);

		// Specular.
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

	}
	


	vec3 result = (ambient + diffuse + specular);
	FragColour = vec4(result , 1.0f);

}