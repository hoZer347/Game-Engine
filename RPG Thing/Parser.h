#pragma once

#include <functional>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

class Parser {
public:
	Parser(std::string);
	bool next();
	
	std::string line;
	std::fstream file;
	std::map<std::string, void*> mem;
	std::function<void(Parser*, std::vector<std::string>&) > f;
};
