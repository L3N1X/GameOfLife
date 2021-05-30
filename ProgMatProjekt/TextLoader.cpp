#include "TextLoader.h"

#include<fstream>
#include<sstream>

TextLoader::TextLoader(std::string& filename)
{
	std::ifstream in(filename);
	if (!in)
	{
		outputString = "ERROR";
	}
	std::string line;
	std::stringstream ss;
	while (getline(in, line))
	{
		ss << "\t\t\t  " << line << std::endl;
	}
	outputString = ss.str();
	in.close();
}

std::string TextLoader::output()
{
	return outputString;
}
