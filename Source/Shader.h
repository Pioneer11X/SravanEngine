#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <assert.h>

class Shader
{
public:

	// Actual Program ID.
	unsigned int ID;

	// Reads and Builds the Shader Program.
	Shader(const GLchar * _vertexPath, const GLchar * _fragmentPath);

	// Use/Activate the Shader
	void use();

	// Some Utility Funcs
	void setBool(const std::string &_name, bool _value) const;
	void setInt(const std::string &_name, int _value) const;
	void setFloat(const std::string &_name, float _value) const;

	~Shader();
};

#endif // !SHADER_H