#include <glm\glm.hpp>
#include <string>

struct Material {

	std::string name;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

	Material( std::string _name, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, float _shininess) {
		name = _name;
		ambient = _ambient;
		diffuse = _diffuse;
		specular = _specular;
		shininess = _shininess;
	};

};