#include "Parser.h"

Parser::Parser(std::string file_name) {
	file = std::fstream(file_name);
}

bool Parser::next() {
	std::string l;
	line = "";

	if (!std::getline(file, l))
		return false;
	
	auto c = l.begin();

	std::string s = "";

	while (c != l.end()) {
		if (*c == '<') {
			line += s;
			s = "";

			while (*c != '>') {
				c++;

				while (*c != ' ' && *c != '>') {
					s += *c;

					c++;
				}

				cmds.push(s);

				s = "";
			}
		} else s += *c;

		if (c == l.end())
			break;

		c++;
	}

	line += s;

	return true;
}
