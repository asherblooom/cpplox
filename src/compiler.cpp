#include "compiler.hpp"
#include <iostream>
#include "scanner.hpp"

void Compiler::Compile(std::string src) {
	Scanner scanner(src);

	int line = -1;
	while (true) {
		Token token = scanner.ScanToken();
		if (token.Line != line) {
			printf("%4d ", token.Line);
			line = token.Line;
		} else {
			printf("   | ");
		}
		printf("%2d '%.*s'\n", token.Type, token.Length, token.Start);

		if (token.Type == TOKEN_EOF) break;
	}
}
