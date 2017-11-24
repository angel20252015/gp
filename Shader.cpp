/*********************************************
Materia: Gráficas Computacionales
Fecha: 24 de Noviembre del 2017
Autor: A01373179 Maria Fernanda Cruz Gonzalez
A01373243 Jose Angel Prado Dupont
**********************************************/
#include "Shader.h"
#include "InputFile.h"
#include <vector>
#include <iostream>

Shader::Shader() {
	_ShaderHandle = 0;
}

Shader::~Shader() {
	glDeleteShader(_ShaderHandle);
}

void Shader::CreateShader(std::string path, GLenum type) {
	InputFile ifile;
	if (!ifile.Read(path)) return;
	std::string source = ifile.GetContents();

	if (_ShaderHandle)
		glDeleteShader(_ShaderHandle);

	_ShaderHandle = glCreateShader(type);

	const GLchar *source_c = (const GLchar*)source.c_str();
	glShaderSource(_ShaderHandle, 1, &source_c, nullptr);

	glCompileShader(_ShaderHandle);

	// Get compile status
	GLint shaderCompileSuccess = 0;
	glGetShaderiv(_ShaderHandle, GL_COMPILE_STATUS, &shaderCompileSuccess);
	if (shaderCompileSuccess == GL_FALSE)
	{
		// Get compile log length
		GLint logLength = 0;
		glGetShaderiv(_ShaderHandle, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0)
		{

			// Allocate memory for compile log
			std::vector<GLchar> compileLog(logLength);

			// Get compile log
			glGetShaderInfoLog(_ShaderHandle, logLength, &logLength, &compileLog[0]);

			// Print compile log
			for (int i = 0; i<logLength; i++)
				std::cout << compileLog[i];
			std::cout << std::endl;
		}
		std::cout << "Shader " << path << " did not compiled." << std::endl;

		//We don't need the shader anymore.
		glDeleteShader(_ShaderHandle);

		return;
	}

	std::cout << "Shader " << path << " compiled successfully" << std::endl;
}

GLuint Shader::GetHandle() {
	return _ShaderHandle;
}