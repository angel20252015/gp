

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