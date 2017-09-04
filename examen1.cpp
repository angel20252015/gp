#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "Circle.h"
#include "InputFile.h"
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <cmath>

//identificador del manager
GLuint vao;

//identificador del manager de los shaders (ShaderProgram)
GLuint shaderProgram;

void Initialize() {//solo se llama una vez; crea toda la memoria que el prgrama va a utilizar
				   //lista de elemntos
	std::vector<glm::vec2> positions;
	//claramente en el CPU y RAM , no tarjeta de video
	//inserta un elemento al final de la lista
	int angulo = 0;
	std::cout << "hola" << angulo << std::endl;
	positions.push_back(glm::vec2(0.0f, 0.0f));
	while (angulo <= 360) {
		std::cout << "angulo" << angulo << std::endl;
		double radian = angulo*0.01745329252f;
		double y = 1*sin(radian);
		double x = 1*cos(radian);
		positions.push_back(glm::vec2(x,y));
		angulo = angulo + 1;
		std::cout << "angulo" << angulo << std::endl;

	}
	//positions.push_back(glm::vec2(-0.25f, 0.5f));	//1
	
											 
	std::vector<glm::vec3>colors;
	//colors.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	float angulo2 = 0;
	colors.push_back(glm::vec3(1.0, 1.0, 1.0));

	while (angulo2 <= 360) {
		double radian = angulo2*0.01745329252f;
		double y = 1 * sin(radian);
		double x = 1 * cos(radian);
		double z = 1 * cos(radian);
		colors.push_back(glm::vec3(x,y,z));
		angulo2 = angulo2 + 1;
	}

	glGenVertexArrays(1, &vao);
	//todos los VBOs creados y configurados 
	glBindVertexArray(vao);
	//identificador del VBO de posiciones
	GLuint positionsVBO;
	//creacion del VBO de posiciones
	glGenBuffers(1, &positionsVBO);//pasa ese numero como referencia 
								   //Ativar el buffer de posiiones para poder utilizarlo
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	//creamos la memoria y la i nicializamos con los datos del atributo de posicoines
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*positions.size(), positions.data(), GL_STATIC_DRAW);
	//Activar el atributo en la tarjeta de video
	glEnableVertexAttribArray(0);
	//configuramos los datos del atributo en la tarjeta de video
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	//ya no usaremos este VBO en este momento
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint colorsVBO;
	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);									//eficiente leer muchas veces
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*colors.size(), colors.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


	//Desactivar manager
	glBindVertexArray(0);

	//crar objeto para leer archivos
	InputFile ifile;

	/*--------------------------- V E R T E X  S H A D E R --------------------------------*/

	//cargar el VERTEX SHADER	
	ifile.Read("DiscardCenter.vert");
	//guardar codigo fuente en un string 
	std::string vertexSource = ifile.getContents();
	//creacion de shader tipo vertex y guardamos su identificador en una variable
	GLuint vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
	const GLchar * vertexSource_c = (const GLchar*)vertexSource.c_str();
	//estamos dando el codigo fuente a OpenGl para que s elo asigne al shader
	glShaderSource(vertexShaderHandle, 1, &vertexSource_c, nullptr);
	//compilar shader en busca de errores
	//asumir que no hay ningun error
	glCompileShader(vertexShaderHandle);

	/*--------------------------- F R A G M E N T  S H A D E R --------------------------------*/

	ifile.Read("DiscardCenter.frag");
	std::string fragmentSource = ifile.getContents();
	GLuint fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar *fragmentSource_c = (const GLchar*)fragmentSource.c_str();
	glShaderSource(fragmentShaderHandle, 1, &fragmentSource_c, nullptr);
	glCompileShader(fragmentShaderHandle);

	//cramos el identificador para le manager de los shaders
	shaderProgram = glCreateProgram();
	//adjuntamos el vertex shader al manager (van a trabajar juntos)
	glAttachShader(shaderProgram, vertexShaderHandle);
	//adjuntamos el fragment shader al manager (van a trabajar juntos)
	glAttachShader(shaderProgram, fragmentShaderHandle);
	//asociamos un uffer con inidice 0 (posiciones) a la variable VertexPosition
	glBindAttribLocation(shaderProgram, 0, "VertexPositon");
	//asociamos un uffer con inidice 1 (colores) a la variable VertexColor
	glBindAttribLocation(shaderProgram, 1, "VertexColor");
	//ejecutamos el proceso de linker (aseguramos que el vertex y fragment son compatibles)
	glLinkProgram(shaderProgram);
}
void GameLoop() {	//Rendereando todo el semestre
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//limpianod buffers

													   //Activamos el vertex shader y el grament shader utilizando el manager
	glUseProgram(shaderProgram);

	//VBOs asociados automaticamente
	glBindVertexArray(vao);//activando el manager


						   //glDrawArrays(GL_TRIANGLE_FAN, 0, 8);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 362);

	//OpenGL viejito, solo para esta clase
	//glBegin(GL_TRIANGLES);

	/*glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-1.0f,-1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(1.0f, -1.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.0f, 1.0f);
	*/

	//	glEnd();

	glBindVertexArray(0);
	//cuando terminas de renderear, cambias los buffers
	glutSwapBuffers();
}

int main(int argc, char* argv[]) {		//Main de pruebas

										//inicializar freeglut
										//Freeglut se encarga de crear una ventana en donde podemos dibujar
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);

	//configuraion de freeGlut
	//iniciar contexto de opeGL(capaidades de la aplicacion grafica) pipeline clasico
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	//glutInitContextProfile(GLUT_CORE_PROFILE);

	//freeglut nos perite configurar eventos que ocurren en la ventana
	//un evento como cuando cierran la venta= limpiar memoria= terminar el programa
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);	//limpiar memoria

																					//Configuramos framebuffer. solicitamos buffer 
																					//					true color	profundidad	segundo buffer para renderear
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	//dimensiones de ventana
	glutInitWindowSize(600, 600);
	//titulo de ventana
	glutCreateWindow("Hello World GL");

	//asociamos una funcion de render para mandar llamar ara dibujar un frame
	glutDisplayFunc(GameLoop);

	//inicializamos Glew para obtener el API de OpenGL de nuestra tarjeta de video
	glewInit();

	//configurar OpenGL
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);	//color por default 

											//llamar initializa
	Initialize();

	glutMainLoop();	//iniciar la aplicaicon (main se pausa en esta linea hasta que se cierre la ventana)


	return 0;


	std::string filename = "Prueba.txt";
	InputFile myFile;
	myFile.Read(filename);
	std::string contents = myFile.getContents();

	std::cout << "Contents: " << contents << std::endl;
	std::cin.get();

}