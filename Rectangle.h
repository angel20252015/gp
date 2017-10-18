#pragma once	
#include <string>

class Rectangle {	//declaracion de la clase Circle
public:
	//Constructores 

	Rectangle();
	Rectangle(float w, float h);
	Rectangle(double r, std::string c);

	float GetWidth();
	float GetHeight();
	float GetArea();
	float GetPerimeter();

	void SetWidth(float w);
	void SetHeight(float h);

private:		//variables
	float _width;
	float _height;
};