#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include "ShaderManager.h"

using std::cout;
using std::endl;

GLuint ShaderManager::LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
{
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		std::cout << "Impossible to open " << vertex_file_path << ". Are you in the right directory?" << std::endl;
		getchar();
		return 0;
	}

	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	std::cout << "Compiling shader : " << vertex_file_path << "...";
	const char* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		std::cout << std::endl << &VertexShaderErrorMessage[0] << std::endl;
	}

	std::cout << "success" << std::endl;

	std::cout << "Compiling shader : " << fragment_file_path << "...";
	const char* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		std::cout << std::endl << &FragmentShaderErrorMessage[0] << std::endl;
	}

	std::cout << "success" << std::endl;

	std::cout << "Linking shader program...";
	GLuint ProgramID = glCreateProgram();
	m_programID = ProgramID;
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 1) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cout << std::endl << &ProgramErrorMessage[0] << std::endl;
	}

	std::cout << "success" << std::endl;

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

void ShaderManager::UseProgram() const
{
	glUseProgram(m_programID);
}

void ShaderManager::setMat4Value(const std::string& name, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void ShaderManager::setVec4Value(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(m_programID, name.c_str()), 1, &value[0]);
}

void ShaderManager::setVec3Value(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(m_programID, name.c_str()), 1, &value[0]);
}

void ShaderManager::setVec2Value(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(m_programID, name.c_str()), 1, &value[0]);
}

void ShaderManager::setFloatValue(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
}

void ShaderManager::setBoolValue(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_programID, name.c_str()), (int)value);
}

void ShaderManager::setIntValue(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
}
ShaderManager::ShaderManager() {}
ShaderManager::~ShaderManager() {}