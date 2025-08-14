#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include "token.hpp"

class Scanner {
public:
	Scanner(std::string src);
	Token ScanToken();

private:
	char* start;
	char* current;
	int line;

	bool match(char expected);
	void skipWhitespace();
};

#endif
