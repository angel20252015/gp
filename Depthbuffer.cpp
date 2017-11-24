/*********************************************
Materia: Gráficas Computacionales
Fecha: 24 de Noviembre del 2017
Autor: A01373179 Maria Fernanda Cruz Gonzalez
A01373243 Jose Angel Prado Dupont
**********************************************/
#include "Depthbuffer.h"

Depthbuffer::Depthbuffer() {
	_framebuffer = 0;	//id del framebuffer	GLuint
	_depthmap = 0;		//id de la textura		GLuint
	_resolution = 0;	//resolucion			GLsizei
}

Depthbuffer::~Depthbuffer() {
	glDeleteTextures(1, &_depthmap);
	glDeleteFramebuffers(1, &_framebuffer);
}

void Depthbuffer::Create(int resolution) {
	_resolution = resolution;

	//crear framebuffer
	glGenFramebuffers(1, &_framebuffer);

	// Activan el framebuffer.
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

	// Configurarlo para no utilizar un buffer de color
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// Crean una textura _depthmap
	glGenTextures(1, &_depthmap);

	// activar la textura
	glBindTexture(GL_TEXTURE_2D, _depthmap);

	// configurar la textura -> filtro / wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	// datos de la textura
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _resolution, _resolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthmap, 0);

	// Desactivar el framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Depthbuffer::Bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
	// viewport
	glViewport(0, 0, _resolution, _resolution);
}

void Depthbuffer::Unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Depthbuffer::BindDepthMap() {
	glBindTexture(GL_TEXTURE_2D, _depthmap);
}

void Depthbuffer::UnbindDepthMap() {
	glBindTexture(GL_TEXTURE_2D, 0);
}