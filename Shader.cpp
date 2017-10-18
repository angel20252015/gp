
#include "Shader.h"
#include "InputFile.h"
#include <vector>

Shader::Shader(){
	_ShaderHandle = 0;
}

Shader::~Shader(){
	glDeleteShader(_ShaderHandle);
}

void Shader::CreateShader(std::string path, GLenum type){
	InputFile ifile;
	if (!ifile.Read(path)) return;
	std::string source = ifile.GetContents();

	if (_ShaderHandle)
		glDeleteShader(_ShaderHandle);

	_ShaderHandle = glCreateShader(type);

	const GLchar *source_c = (const GLchar*)source.c_str();
	glShaderSource(_ShaderHandle, 1, &source_c, nullptr);

	glCompileShader(_ShaderHandle);
}

GLuint Shader::GetHandle(){
	return _ShaderHandle;
}
