
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "Camera.h"

Mesh _mesh;
ShaderProgram _shaderProgram;
Transform _transform;
Transform _transform2;
Camera _camera; //camera 3D
float grados = 0;
float radianes;
float escala = 0.5f;
bool cambio = false;
float escalar = 1;


void Initialize()
{

	// Creando toda la memoria que el programa va a utilizar.

	// Creación del atributo de posiciones de los vértices.
	// Lista de vec2
	// Claramente en el CPU y RAM
	std::vector<glm::vec3> positions;
	std::vector<unsigned int> indices;
	
	//adelante
	positions.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	positions.push_back(glm::vec3(-1.0f, -1.0f, 1));
	positions.push_back(glm::vec3(1.0f, -1.0f, 1));
	positions.push_back(glm::vec3(-1.0f, -1.0f, -1));
	positions.push_back(glm::vec3(1.0f, -1.0f, -1));

	indices.push_back(0);
	indices.push_back(1); 
	indices.push_back(2); 

	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(1);

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(4);

	indices.push_back(0);
	indices.push_back(4);
	indices.push_back(3);

	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(1);

	indices.push_back(4);
	indices.push_back(2);
	indices.push_back(1);

	std::vector<glm::vec3> colors;
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	
	_mesh.SetIndices(indices, GL_STATIC_DRAW);
	_mesh.CreateMesh(5);
	_mesh.SetPositionAttribute(positions, GL_STATIC_DRAW, 0);
	_mesh.SetColorAttribute(colors, GL_STATIC_DRAW, 1);
	_mesh.SetIndices(indices, GL_STATIC_DRAW);
	

	_shaderProgram.CreateProgram();
	_shaderProgram.AttachShader("Default.vert", GL_VERTEX_SHADER);
	_shaderProgram.AttachShader("Default.frag", GL_FRAGMENT_SHADER);
	_shaderProgram.SetAttribute(0, "VertexPosition");
	_shaderProgram.SetAttribute(1, "VertexColor");
	_shaderProgram.LinkProgram();
	//_camera.SetOrthigraphic(4.0f,4.0f);
	_camera.MoveForward(15.0f);
	//_transform.SetRotation(0.0f,0.0f, 90.0f);
	_transform.SetScale(3, 3, 3);
}

void GameLoop()
{
	if (escala > 1 && !cambio) { escalar = escalar= escalar*-1 ; cambio = true; }
	if (escala < 0.25 && cambio) { escalar = escalar = escalar*-1; cambio = false; }
	escala = 0.0001*escalar + escala;
	_transform2.SetScale(escala,escala,escala);
	grados = grados + 0.01;
	radianes = grados*0.0174533f;
	_transform.SetPosition(5*cos(radianes),5*sin(radianes),0);
	// Limpiamos el buffer de color y el buffer de profunidad.
	// Siempre hacerlo al inicio del frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//_camera.MoveForward(-0.0001f);

	//_transform.Rotate(0.0f, 0.01f, 0.0f, false);//a lo largo de los ejes locales
	_transform2.Rotate(-0.01f, -0.01f, -0.01f, true);//a lo largo de los ejes globales
	_transform.Rotate(0.01f, 0.01f, 0.01f, false);
	

	_shaderProgram.Activate();
	_shaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform.GetModelMatrix());
	_mesh.Draw(GL_TRIANGLES);
	_shaderProgram.SetUniformMatrix("mvpMatrix", _camera.GetViewProjection() * _transform2.GetModelMatrix());
	_mesh.Draw(GL_TRIANGLES);
	_shaderProgram.Deactivate();

	// Cuando terminamos de renderear, cambiamos los buffers.
	glutSwapBuffers();
}

void Idle()
{
	// Cuando OpenGL entra en modo de reposo 
	// (para guardar bateria, por ejemplo)
	// le decimos que vuelva a dibujar ->
	// Vuelve a mandar a llamar GameLoop
	glutPostRedisplay();
}

void ReshapeWindow(int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(int argc, char* argv[])
{
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
	glutInitWindowSize(600, 600);
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