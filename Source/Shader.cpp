#include "Shader.h"


using namespace std;

Shader::Shader(const GLchar * _vertexPath, const GLchar * _fragmentPath)
{

	string vertexCode;
	string fragmentCode;

	ifstream vShaderFile;
	ifstream fShaderFile;

	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	try {
		// Open the files.
		vShaderFile.open(_vertexPath);
		fShaderFile.open(_fragmentPath);

		stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// Close the files.
		vShaderFile.close();
		fShaderFile.close();

		// Convert the stream to string.
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (ifstream::failure e) {
		std::cout << "ERROR::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char * vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// Check for Compilation Errors.
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(vertex, 512, NULL, infoLog);
	assert(success);

	// vertex Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(fragment, 512, NULL, infoLog);
	assert(success);


	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	// print linking errors if any
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	glGetProgramInfoLog(ID, 512, NULL, infoLog);
	assert(success);

	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::use()
{
	glUseProgram(this->ID);
}

void Shader::setBool(const std::string & _name, bool _value) const
{
	glUniform1i(glGetUniformLocation(ID, _name.c_str()), (int)_value);
}

void Shader::setInt(const std::string & _name, int _value) const
{
	glUniform1i(glGetUniformLocation(ID, _name.c_str()), _value);
}

void Shader::setFloat(const std::string & _name, float _value) const
{
	glUniform1f(glGetUniformLocation(ID, _name.c_str()), _value);
}

void Shader::setVec3(const std::string & _name, glm::vec3 _value) const
{
	glUniform3f(glGetUniformLocation(ID, _name.c_str()), _value.x, _value.y, _value.z);
}

void Shader::setMat4(const std::string & _name, glm::mat4 _value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, _name.c_str()), 1, GL_FALSE, &_value[0][0]);
}

Shader::~Shader()
{
}
