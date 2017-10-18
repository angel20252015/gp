/*********************************************
Materia: Gráficas Computacionales
Fecha: 20 de Agosto del 2017
Autor: A01373179 Maria Fernanda Cruz Gonzalez
**********************************************/
#pragma once
#include <string>

class InputFile {
private:
	std::string _contents;

public:
	bool Read(std::string _fileName);
	std::string GetContents();
};