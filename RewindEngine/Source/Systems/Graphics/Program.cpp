#include <precompiled.h>

/*
File: Program.cpp
Author: David Westen
Date Created: 1/16/2017

Modified by(optional):
Date Modified(optional):

Purpose (optional):
*/


#include <Systems/Graphics/Program.h>

#include <GL/glew.h>
#include <GL/GL.h>

#include <cstdlib>
#include <cstdio>

using namespace Graphics;

#pragma region "Constructors/Destructor"

Program::Program() : m_handle(0)
{

}


Program::~Program()
{
}

#pragma endregion

#pragma region "Public Methods"

void Program::Use()
{
	glUseProgram(m_handle);
}

void Program::Unuse()
{
	glUseProgram(0);
}

void Program::SetUniform(char const * name, math::mat4<float> const & matrix)
{
	GLint location = glGetUniformLocation(m_handle, name);
	if (location != -1)
		glProgramUniformMatrix4fv(m_handle, location, 1, GL_TRUE, &matrix.m[0][0]);
}

void Program::SetUniform(char const * name, math::mat3<float> const & matrix)
{
	GLint location = glGetUniformLocation(m_handle, name);
	if (location != -1)
		glProgramUniformMatrix3fv(m_handle, location, 1, GL_TRUE, &matrix.m[0][0]);
}

void Program::SetUniform(char const * name, math::vec3<float> const & vector)
{
	GLint location = glGetUniformLocation(m_handle, name);
	if (location != -1)
		glProgramUniform3f(m_handle, location, vector.x, vector.y, vector.z);
}

void Program::SetUniform(char const * name, math::vec2<float> const & vector)
{
	GLint location = glGetUniformLocation(m_handle, name);
	if (location != -1)
		glProgramUniform2f(m_handle, location, vector.x, vector.y);
}

void Program::SetUniform(char const * name, float const & value)
{
	GLint location = glGetUniformLocation(m_handle, name);
	if (location != -1)
		glProgramUniform1f(m_handle, location, value);
}

void Program::SetUniform(char const * name, int const & value)
{
	GLint location = glGetUniformLocation(m_handle, name);
	if (location != -1)
		glProgramUniform1i(m_handle, location, value);
}

void Program::CreateHandle()
{
	m_handle = glCreateProgram();
}

void Program::DestroyHandle()
{
	glDeleteProgram(m_handle);
}

void Program::AttachShader(ShaderType const & type, char const * sourcePath)
{
	FILE * file;
	fopen_s(&file, sourcePath, "rb");

	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char * source = (char*)malloc(length+1);
	fread_s(source, length, 1, length, file);
	source[length] = 0;

	fclose(file);

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, &length);
	free(source);

	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_TRUE) {
		glAttachShader(m_handle, shader);
	}
	else
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char * infoLog = (char*)malloc(length);
		glGetShaderInfoLog(shader, length, &length, infoLog);
		free(infoLog);
	}
	glDeleteShader(shader);
}

void Program::Link()
{
	glLinkProgram(m_handle);

	GLint status;
	glGetProgramiv(m_handle, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		int error = 45;
		//report error;
	}
}

#pragma endregion