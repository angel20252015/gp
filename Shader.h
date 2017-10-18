/***************************
Materia: Gráficas Computacionales
Fecha : 02 de Octubre del 2017
Autor : A01373179 Maria Fernanda Cruz Gonzalez
**********************************************/
#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

	class Shader {	
	public:
		Shader();
		~Shader();
		void CreateShader(std::string path, GLenum type);
		GLuint GetHandle();

	private:		//variables
		GLuint _ShaderHandle = 0;
};
