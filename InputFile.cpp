/*********************************************************
Materia: Gráficas Computacionales
Fecha: 09 de Agosto del 2017
Autor: A01168958 Francisco Geada Rodríguez
*********************************************************/

//Hecho con base en http://www.cplusplus.com/reference/fstream/fstream/

#include "InputFile.h"
#include <sstream>
#include <fstream>
#include <iostream>

bool InputFile::Read(std::string fileName) {
	bool open = false;
	std::ifstream inputFile;
	inputFile.open(fileName);
	std::string line;
	InputFile::contents = "";

	if (inputFile.is_open()) {
		open = true;

		while (getline(inputFile, line)) {
			InputFile::contents += line;
			InputFile::contents += "\n";
		}

		inputFile.close();
	}

	return open;
}

std::string InputFile::getContents() {
	return InputFile::contents;
}