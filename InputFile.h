#pragma once
#include <string>

class InputFile {
private:
	std::string contents;

public:
	bool Read(std::string fileName);
	std::string getContents();

};