/*********************************************
Materia: Gráficas Computacionales
Fecha: 20 de Octubre del 2017
Autor: A01373179 Maria Fernanda Cruz Gonzalez
A01373243 Jose Angel Prado Dupont
**********************************************/
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "Camera.h"
#include "Texture2D.h"
#include <IL/il.h>
#include "Depthbuffer.h"

Mesh _mesh;
Mesh _mesh2;
ShaderProgram _shaderProgram;
ShaderProgram _shaderProgramDepth;

Transform _transform;
Transform _transform2;
Transform _ctransform1;
Transform _ctransform2;
Transform _ctransform3;
Transform _ctransform4; 
Transform _ctransform11;
Transform _ctransform22;
Transform _ctransform33;
Transform _ctransform44;
Camera _camera; //camera 3D
Camera _cameraLuz;

Texture2D _texture;
Texture2D _texture1;

Depthbuffer _depthBuffer;

float rota = 0;
float rotar = 0.01;

void Initialize() {

	// Creando toda la memoria que el programa va a utilizar.
	// Creación del atributo de posiciones de los vértices.
	// Lista de vec2
	// Claramente en el CPU y RAM
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> positions2;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;
	std::vector<glm::vec2> texturas;
	_texture.LoadTexture("caja.jpg");
	_texture1.LoadTexture("cuadros.jpg");


	//adelante
	positions.push_back(glm::vec3(-2.0f, -4.0f, 0.250f));
	positions.push_back(glm::vec3(2.0f, 4.0f, 0.250f));
	positions.push_back(glm::vec3(-2.0f, 4.0f, 0.250f));
	positions.push_back(glm::vec3(2.0f, -4.0f, 0.250f));

	positions2.push_back(glm::vec3(-0.50f, -1, 0.250f));
	positions2.push_back(glm::vec3(0.50f, 1, 0.250f));
	positions2.push_back(glm::vec3(-0.50f, 1, 0.250f));
	positions2.push_back(glm::vec3(0.50f, -1, 0.250f));

	//positions.push_back(glm::vec3(3.0f, 3.0f, 3.0f));
	//positions.push_back(glm::vec3(-3.0f, -3.0f, 3.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1));

	texturas.push_back(glm::vec2(0.0f, 0.0f));
	texturas.push_back(glm::vec2(1.0f, 1.0f));
	texturas.push_back(glm::vec2(0.0f, 1.0f));
	texturas.push_back(glm::vec2(1.0f, 0.0f));

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(0);

	//izquierda
	positions.push_back(glm::vec3(-2.0f, 4.0f, 0.250f));
	positions.push_back(glm::vec3(-2.0f, -4.0f, -0.250f));
	positions.push_back(glm::vec3(-2.0f, -4.0f, 0.250f));
	positions.push_back(glm::vec3(-2.0f, 4.0f, -0.250f));

	positions2.push_back(glm::vec3(-0.50f, 1, 0.250f));
	positions2.push_back(glm::vec3(-0.50f, -1, -0.250f));
	positions2.push_back(glm::vec3(-0.50f, -1, 0.250f));
	positions2.push_back(glm::vec3(-0.50f, 1, -0.250f));
	//positions.push_back(glm::vec3(-3.0f, -3.0f, -3.0f));
	//positions.push_back(glm::vec3(-3.0f, 3.0f, 3.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));


	texturas.push_back(glm::vec2(0.0f, 0.0f));
	texturas.push_back(glm::vec2(1.0f, 1.0f));
	texturas.push_back(glm::vec2(0.0f, 1.0f));
	texturas.push_back(glm::vec2(1.0f, 0.0f));

	indices.push_back(4);
	indices.push_back(5);
	indices.push_back(6);
	indices.push_back(7);
	indices.push_back(5);
	indices.push_back(4);

	//atras
	positions.push_back(glm::vec3(-2.0f, 4.0f, -0.250f));
	positions.push_back(glm::vec3(2.0f, 4.0f, -0.250f));
	positions.push_back(glm::vec3(-2.0f, -4.0f, -0.250f));
	//positions.push_back(glm::vec3(-3.0f, -3.0f, -3.0f));
	//positions.push_back(glm::vec3(3.0f, 3.0f, -3.0f));
	positions.push_back(glm::vec3(2.0f, -4.0f, -0.250f));

	positions2.push_back(glm::vec3(-0.5f, 1.0f, -0.250f));
	positions2.push_back(glm::vec3(0.50f, 1, -0.250f));
	positions2.push_back(glm::vec3(-0.5f, -1, -0.250f));
	//positions.push_back(glm::vec3(-3.0f, -3.0f, -3.0f));
	//positions.push_back(glm::vec3(3.0f, 3.0f, -3.0f));
	positions2.push_back(glm::vec3(0.50f, -1, -0.250f));

	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));


	texturas.push_back(glm::vec2(0.0f, 0.0f));
	texturas.push_back(glm::vec2(1.0f, 0.0f));
	texturas.push_back(glm::vec2(0.0f, 1.0f));
	texturas.push_back(glm::vec2(1.0f, 1.0f));

	indices.push_back(8);
	indices.push_back(9);
	indices.push_back(10);
	indices.push_back(10);
	indices.push_back(9);
	indices.push_back(11);

	//derecha
	positions.push_back(glm::vec3(2.0f, -4.0f, -0.250f));
	positions.push_back(glm::vec3(2.0f, 4.0f, 0.250f));
	positions.push_back(glm::vec3(2.0f, -4.0f, 0.250f));
	positions.push_back(glm::vec3(2.0f, 4.0f, -0.250f));
	//positions.push_back(glm::vec3(3.0f, 3.0f, 3.0f));
	//positions.push_back(glm::vec3(3.0f, -3.0f, -3.0f));

	positions2.push_back(glm::vec3(0.50f, -1, -0.250f));
	positions2.push_back(glm::vec3(0.50f, 1, 0.250f));
	positions2.push_back(glm::vec3(0.50f, -1, 0.250f));
	positions2.push_back(glm::vec3(0.5f, 1, -0.250f));

	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	texturas.push_back(glm::vec2(0.0f, 0.0f));
	texturas.push_back(glm::vec2(1.0f, 1.0f));
	texturas.push_back(glm::vec2(0.0f, 1.0f));
	texturas.push_back(glm::vec2(1.0f, 0.0f));

	indices.push_back(12);
	indices.push_back(13);
	indices.push_back(14);
	indices.push_back(15);
	indices.push_back(13);
	indices.push_back(12);

	//Arriba
	positions.push_back(glm::vec3(-2.0f, 4.0f, -0.250f));
	positions.push_back(glm::vec3(-2.0f, 4.0f, 0.250f));
	positions.push_back(glm::vec3(2.0f, 4.0f, -0.250f));
	//positions.push_back(glm::vec3(3.0f, 3.0f, -3.0f));
	//positions.push_back(glm::vec3(-3.0f, 3.0f, 3.0f));
	positions.push_back(glm::vec3(2.0f, 4.0f, 0.50f));

	positions2.push_back(glm::vec3(-0.50f, 1, -0.250f));
	positions2.push_back(glm::vec3(-0.50f, 1, 0.250f));
	positions2.push_back(glm::vec3(0.50f, 1, -0.250f));
	//positions.push_back(glm::vec3(3.0f, 3.0f, -3.0f));
	//positions.push_back(glm::vec3(-3.0f, 3.0f, 3.0f));
	positions2.push_back(glm::vec3(0.50f, 1, 0.250f));

	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

	texturas.push_back(glm::vec2(0.0f, 0.0f));
	texturas.push_back(glm::vec2(1.0f, 0.0f));
	texturas.push_back(glm::vec2(0.0f, 1.0f));
	texturas.push_back(glm::vec2(1.0f, 1.0f));

	indices.push_back(16);
	indices.push_back(17);
	indices.push_back(18);
	indices.push_back(18);
	indices.push_back(17);
	indices.push_back(19);

	//abajo
	positions.push_back(glm::vec3(-2.0f, -4.0f, 0.250f));
	positions.push_back(glm::vec3(-2.0f, -4.0f, -0.250f));
	positions.push_back(glm::vec3(2.0f, -4.0f, -0.250f));
	//positions.push_back(glm::vec3(3.0f, -3.0f, -3.0f));
	positions.push_back(glm::vec3(2.0f, -4.0f, 0.250f));
	//positions.push_back(glm::vec3(-3.0f, -3.0f, 3.0f));

	positions2.push_back(glm::vec3(-0.50f, -1, 0.250f));
	positions2.push_back(glm::vec3(-0.50f, -1, -0.250f));
	positions2.push_back(glm::vec3(0.50f, -1, -0.250f));
	//positions.push_back(glm::vec3(3.0f, -3.0f, -3.0f));
	positions2.push_back(glm::vec3(0.50f, -1, 0.250f));
	//positions.push_back(glm::vec3(-3.0f, -3.0f, 3.0f));

	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));

	texturas.push_back(glm::vec2(0.0f, 0.0f));
	texturas.push_back(glm::vec2(0.0f, 1.0f));
	texturas.push_back(glm::vec2(1.0f, 1.0f));
	texturas.push_back(glm::vec2(1.0f, 0.0f));

	indices.push_back(20);
	indices.push_back(21);
	indices.push_back(22);
	indices.push_back(22);
	indices.push_back(23);
	indices.push_back(20);


	// Arreglo de colores en el cpu
	std::vector<glm::vec3> colors;
	//colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	//colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	_depthBuffer.Create(2048);
	_mesh.SetIndices(indices, GL_STATIC_DRAW);
	_mesh.CreateMesh(24);
	_mesh.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);
	_mesh.SetColorAttribute(colors, GL_STATIC_DRAW, 1);
	_mesh.SetIndices(indices, GL_STATIC_DRAW);
	_mesh.SetNormalAttribute(normals, GL_STATIC_DRAW, 2);
	_mesh.SetTexCoordAttribute(texturas, GL_STATIC_DRAW, 3);

	_mesh2.SetIndices(indices, GL_STATIC_DRAW);
	_mesh2.CreateMesh(24);
	_mesh2.SetPositionAttribute(positions2, GL_STATIC_DRAW, 0);
	_mesh2.SetColorAttribute(colors, GL_STATIC_DRAW, 1);
	_mesh2.SetIndices(indices, GL_STATIC_DRAW);
	_mesh2.SetNormalAttribute(normals, GL_STATIC_DRAW, 2);
	_mesh2.SetTexCoordAttribute(texturas, GL_STATIC_DRAW, 3);

	_shaderProgram.CreateProgram();
	_shaderProgramDepth.CreateProgram();
	_shaderProgram.AttachShader("Default.vert", GL_VERTEX_SHADER);
	_shaderProgram.AttachShader("Default.frag", GL_FRAGMENT_SHADER);
	_shaderProgramDepth.AttachShader("Depth.vert", GL_VERTEX_SHADER);
	_shaderProgramDepth.AttachShader("Depth.frag", GL_FRAGMENT_SHADER);
	_shaderProgram.SetAttribute(0, "VertexPosition");
	_shaderProgram.SetAttribute(1, "VertexColor");
	_shaderProgram.SetAttribute(2, "VertexNormal");
	_shaderProgram.SetAttribute(3, "VertexTexCoord");
	_shaderProgramDepth.SetAttribute(0, "VertexPosition");
	_shaderProgram.LinkProgram();
	_shaderProgramDepth.LinkProgram();
	_cameraLuz.SetOrthigraphic(40.0f, 1.0f);
	_cameraLuz.SetPosition(0, 10, 0);
	_cameraLuz.Pitch(-90);
	//_camera.SetOrthigraphic(4.0f,4.0f);
	_camera.MoveForward(25.0f);
	_camera.SetRotation(-30,0,0);
	_camera.MoveUp(10);
	_transform.MoveUp(-5, true);
	_transform2.SetScale(150, 0.5, 150);
	_transform2.MoveUp(-10, true);
	_ctransform1.MoveUp(5.3f, true);
	_ctransform1.MoveRight(-1.7,true);
	_ctransform2.MoveUp(5.3f, true);
	//_ctransform2.MoveRight(-1.8, true);
	_ctransform3.MoveUp(5.3f, true);
	_ctransform3.MoveRight(1.7, true);
	_ctransform4.MoveUp(-2.3f, true);
	_ctransform4.MoveRight(-3.1f, true);
	_ctransform4.Rotate(0,0,80, true);

	_ctransform11.MoveUp(2.3f, true);
	//_ctransform11.MoveRight(-1.8, true);
	_ctransform22.MoveUp(2.3f, true);
	//_ctransform2.MoveRight(-1.8, true);
	_ctransform33.MoveUp(2.3f, true);
	//_ctransform33.MoveRight(1.8, true);
	//_ctransform44.MoveUp(-2.3f, true);
	_ctransform44.MoveUp(2.3f, true);
	//_ctransform44.Rotate(0, 0, 80, true);
	//_ctransform1.SetScale(0.3334f, 0.5f, 0.1f);
	//_transform.SetScale(1, 1.5f, 0.1f);
	//_transform.SetRotation(0.0f,0.0f, 90.0f);
	/**/
	_transform.Rotate(-60.0f, 0.00f, 0.0f, true);
	rota = 0;
	rotar = 0.05;
}

void GameLoop() {
	_transform.Rotate(0.0f, 0.1f, 0.0f, true);//a lo largo de los ejes globales
	if (rota >= 120 || rota<0) {
		rotar = rotar*-1;
	}
	rota = rota + rotar;
	_ctransform1.MoveForward(rotar / 50, false);
	_ctransform1.Rotate(rotar, 0, 0.0f, false);
	_ctransform2.MoveForward(rotar*0.9 / 50, false);
	_ctransform2.Rotate(rotar*0.9, 0, 0.0f, false);
	_ctransform3.MoveForward(rotar*0.7 / 50, false);
	_ctransform3.Rotate(rotar*0.7, 0, 0.0f, false);
	_ctransform4.MoveForward(rotar*0.8 / 50, false);
	_ctransform4.Rotate(rotar*0.8, 0, 0.0f, false);

	_ctransform11.MoveForward(rotar / 50, false);
	_ctransform11.Rotate(rotar, 0, 0.0f, false);
	_ctransform22.MoveForward(rotar*0.9 / 50, false);
	_ctransform22.Rotate(rotar*0.9, 0, 0.0f, false);
	_ctransform33.MoveForward(rotar*0.7 / 50, false);
	_ctransform33.Rotate(rotar*0.7, 0, 0.0f, false);
	_ctransform44.MoveForward(rotar*0.8 / 50, false);
	_ctransform44.Rotate(rotar*0.8, 0, 0.0f, false);
	// Limpiamos el buffer de color y el buffer de profunidad.
	// Siempre hacerlo al inicio del frame
	_depthBuffer.Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shaderProgramDepth.Activate();
	_shaderProgramDepth.SetUniformMatrix("mvpMatrix", _cameraLuz.GetViewProjection() * _transform.GetModelMatrix());
	_mesh.Draw(GL_TRIANGLES);
	_shaderProgramDepth.SetUniformMatrix("mvpMatrix", _cameraLuz.GetViewProjection() * _transform.GetModelMatrix()*_ctransform1.GetModelMatrix());
	_mesh2.Draw(GL_TRIANGLES);
	_shaderProgramDepth.SetUniformMatrix("mvpMatrix", _cameraLuz.GetViewProjection() * _transform.GetModelMatrix()*_ctransform2.GetModelMatrix());
	_mesh2.Draw(GL_TRIANGLES);
	_shaderProgramDepth.SetUniformMatrix("mvpMatrix", _cameraLuz.GetViewProjection() * _transform.GetModelMatrix()*_ctransform3.GetModelMatrix());
	_mesh2.Draw(GL_TRIANGLES);
	_shaderProgramDepth.SetUniformMatrix("mvpMatrix", _cameraLuz.GetViewProjection() * _transform.GetModelMatrix()*_ctransform4.GetModelMatrix());
	_mesh2.Draw(GL_TRIANGLES);

	_shaderProgramDepth.SetUniformMatrix("mvpMatrix", _cameraLuz.GetViewProjection() * _transform.GetModelMatrix()*_ctransform1.GetModelMatrix()*_ctransform11.GetModelMatrix());
	_mesh2.Draw(GL_TRIANGLES);
	_shaderProgramDepth.SetUniformMatrix("mvpMatrix", _cameraLuz.GetViewProjection() * _transform.GetModelMatrix()*_ctransform2.GetModelMatrix()*_ctransform22.GetModelMatrix());
	_mesh2.Draw(GL_TRIANGLES);
	_shaderProgramDepth.SetUniformMatrix("mvpMatrix", _cameraLuz.GetViewProjection() * _transform.GetModelMatrix()*_ctransform3.GetModelMatrix()*_ctransform33.GetModelMatrix());
	_mesh2.Draw(GL_TRIANGLES);
	_shaderProgramDepth.SetUniformMatrix("mvpMatrix", _cameraLuz.GetViewProjection() * _transform.GetModelMatrix()*_ctransform4.GetModelMatrix()*_ctransform44.GetModelMatrix());
	_mesh2.Draw(GL_TRIANGLES);
	_shaderProgramDepth.SetUniformMatrix("mvpMatrix", _cameraLuz.GetViewProjection() * _transform2.GetModelMatrix());
	_mesh.Draw(GL_TRIANGLES);
	_depthBuffer.Unbind();
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	_shaderProgramDepth.Deactivate();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//_camera.MoveForward(-0.0001f);

	//_transform.Rotate(0.0f, 0.01f, 0.0f, false);//a lo largo de los ejes locales
	
	_shaderProgram.Activate();
	_shaderProgram.SetUniformf("pluzx", 0);
	_shaderProgram.SetUniformf("pluzy", 10);
	_shaderProgram.SetUniformf("pluzz", 0);
	_shaderProgram.SetUniformf("pcamarax", _camera.GetPosition()[0]);
	_shaderProgram.SetUniformf("pcamaray", _camera.GetPosition()[1]);
	_shaderProgram.SetUniformf("pcamaraz", _camera.GetPosition()[2]);
	_shaderProgram.SetUniformi("DiffuseTexture", 0);
	_shaderProgram.SetUniformMatrix("LightVPMatrix", _cameraLuz.GetViewProjection());
	_shaderProgram.SetUniformi("ShadowMap", 1);
	

	glActiveTexture(GL_TEXTURE0);
	_texture1.Bind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.BindDepthMap();

	_shaderProgram.SetUniformMatrix("ModelMatrix", _transform2.GetModelMatrix());
	_shaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform2.GetModelMatrix());
	_mesh.Draw(GL_TRIANGLES);

	glActiveTexture(GL_TEXTURE0);
	_texture1.Unbind();
	glActiveTexture(GL_TEXTURE1);
	glActiveTexture(GL_TEXTURE0);
	_texture.Bind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.BindDepthMap();
	_shaderProgram.SetUniformMatrix("ModelMatrix", _transform.GetModelMatrix());
	_shaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix());
	_mesh.Draw(GL_TRIANGLES);

	_shaderProgram.SetUniformMatrix("ModelMatrix", _transform.GetModelMatrix()*_ctransform1.GetModelMatrix());
	_shaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix()*_ctransform1.GetModelMatrix());
	_mesh2.Draw(GL_TRIANGLES);
	
	_shaderProgram.SetUniformMatrix("ModelMatrix", _transform.GetModelMatrix()*_ctransform2.GetModelMatrix());
	_shaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix()*_ctransform2.GetModelMatrix());
	_mesh2.Draw(GL_TRIANGLES);
	
	_shaderProgram.SetUniformMatrix("ModelMatrix", _transform.GetModelMatrix()*_ctransform3.GetModelMatrix());
	_shaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix()*_ctransform3.GetModelMatrix());
	_mesh2.Draw(GL_TRIANGLES);
	
	_shaderProgram.SetUniformMatrix("ModelMatrix", _transform.GetModelMatrix()*_ctransform4.GetModelMatrix());
	_shaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix()*_ctransform4.GetModelMatrix());
	_mesh2.Draw(GL_TRIANGLES);
	
	_shaderProgram.SetUniformMatrix("ModelMatrix", _transform.GetModelMatrix()*_ctransform1.GetModelMatrix()*_ctransform11.GetModelMatrix());
	_shaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix()*_ctransform1.GetModelMatrix()*_ctransform11.GetModelMatrix());
	_mesh2.Draw(GL_TRIANGLES);
	
	_shaderProgram.SetUniformMatrix("ModelMatrix", _transform.GetModelMatrix()*_ctransform2.GetModelMatrix()*_ctransform22.GetModelMatrix());
	_shaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix()*_ctransform2.GetModelMatrix()*_ctransform22.GetModelMatrix());
	_mesh2.Draw(GL_TRIANGLES);
	
	_shaderProgram.SetUniformMatrix("ModelMatrix", _transform.GetModelMatrix()*_ctransform3.GetModelMatrix()*_ctransform33.GetModelMatrix());
	_shaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix()*_ctransform3.GetModelMatrix()*_ctransform33.GetModelMatrix());
	_mesh2.Draw(GL_TRIANGLES);
	
	_shaderProgram.SetUniformMatrix("ModelMatrix", _transform.GetModelMatrix()*_ctransform4.GetModelMatrix()*_ctransform44.GetModelMatrix());
	_shaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix()*_ctransform4.GetModelMatrix()*_ctransform44.GetModelMatrix());
	_mesh2.Draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	_texture.Unbind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.UnbindDepthMap();
	
	_shaderProgram.Deactivate();

	// Cuando terminamos de renderear, cambiamos los buffers.
	glutSwapBuffers();
}

void Idle() {
	// Cuando OpenGL entra en modo de reposo 
	// (para guardar bateria, por ejemplo)
	// le decimos que vuelva a dibujar ->
	// Vuelve a mandar a llamar GameLoop
	glutPostRedisplay();
}

void ReshapeWindow(int width, int height) {
	glViewport(0, 0, width, height);
}

int main(int argc, char* argv[]) {
	// Inicializar freeglut
	// Freeglut se encarga de crear una ventana
	// en donde podemos dibujar
	glutInit(&argc, argv);
	// Solicitando una versión específica de OpenGL.
	//glutInitContextVersion(4, 4);
	// Iniciar el contexto de OpenGL. El contexto se refiere
	// a las capacidades que va a tener nuestra aplicación
	// gráfica.
	// En este caso estamos trabajando con el pipeline programable.
	glutInitContextProfile(GLUT_CORE_PROFILE);
	// Freeglut nos permite configurar eventos que ocurren en la ventana.
	// Un evento que nos interesa es cuando alguien cierra la ventana.
	// En este caso, simplemente dejamos de renderear la esscena y terminamos el programa.
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	// Configuramos el framebuffer. En este caso estamos solicitando un buffer
	// true color RGBA, un buffer de profundidad y un segundo buffer para renderear.
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	// Iniciar las dimensiones de la ventana (en pixeles)
	glutInitWindowSize(1080, 1080);
	// Creamos la ventana y le damos un título.
	glutCreateWindow("Hello World GL");
	// Asociamos una función de render.
	//Esta función se mandará a llamar para dibujar un frame.
	glutDisplayFunc(GameLoop);
	// Asociamos una función para el cambio de resolución
	// de la ventana. Freeglut la va a mandar a llamar
	// cuando alguien cambie el tamaño de la venta.
	glutReshapeFunc(ReshapeWindow);
	// Asociamos la función que se mandará a llamar
	// cuando OpenGL entre en modo de reposo.
	glutIdleFunc(Idle);

	// Inicializar GLEW. Esta librería se encarga de obtener el API de OpenGL de
	// nuestra tarjeta de video. SHAME ON YOU MICROSOFT.
	glewInit();
	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	// Configurar OpenGL. Este es el color por default del buffer de color
	// en el framebuffer.
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);

	// Ademas de solicitar el buffer de profundidad, tenemos
	// que decirle a OpenGL que lo queremos activo
	glEnable(GL_DEPTH_TEST);
	// Activamos el borrado de caras traseras.
	// Ahora todos los triangulos que dibujemos deben estar en CCW
	glEnable(GL_CULL_FACE);
	// No dibujar las caras traseras de las geometrías.
	glCullFace(GL_BACK);

	std::cout << glGetString(GL_VERSION) << std::endl;

	// Configuración inicial de nuestro programa.
	Initialize();

	// Iniciar la aplicación. El main se pausará en esta línea hasta que se cierre
	// la venta de OpenGL.
	glutMainLoop();
	return 0;
}
