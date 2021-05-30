#pragma once
#include<string>
class TextLoader
{
private:
	std::string filename;
	std::string outputString;
public:
	TextLoader(std::string& filename);
	std::string output();
};

