#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#include <IL/il.h>
#include <GL/glew.h>

class Depthbuffer {
public:
	Depthbuffer();
	~Depthbuffer();
	void Create(int resolution);
	void Bind();
	void Unbind();
	void BindDepthMap();
	void UnbindDepthMap();

private:
	GLuint _framebuffer;	//id del framebuffer
	GLuint _depthmap;		//id de la textura
	GLsizei _resolution;	//resolucion de la textura
};