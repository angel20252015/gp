#pragma once	//Para poder utilizarlo en cualquier otro archivo - incluir referecia a esta clase sin copiar todo el archivo
#include <string>

class Circle {	//declaracion de la clase Circle
public:
	//Constructores 

	Circle();
	Circle(double r);
	Circle(double r, std::string c);

	double GetArea();
	double GetRadius();
	std::string GetColor();
	void SetRadius(double r);
	void SetColor(std::string c);

private:		//variables
	double _radius;
	std::string _color;
};

