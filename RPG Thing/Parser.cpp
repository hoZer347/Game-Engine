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
	std::vector<std::string> v;

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

				v.push_back(s);

				s = "";
			}
		} else s += *c;

		if (c == l.end())
			break;

		c++;
	}

	f(this, v);

	line += s;

	return true;
}
