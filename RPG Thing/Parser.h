#pragma once

#include <fstream>
#include <queue>
#include <string>

class Parser {
public:
	Parser(std::string);
	bool next();
	
	std::string line;
	std::fstream file;
	std::queue<std::string> cmds;
};
