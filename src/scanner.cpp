#include "scanner.hpp"

Scanner::Scanner(std::string src) {
	start = &src[0];
	current = &src[0];
	line = 1;
}

Token Scanner::ScanToken() {
	start = current;
	if (*current == '\0')
		return Token(TOKEN_EOF, start, current - start, line);

	skipWhitespace();

	char c = *current;
	current++;

	// clang-format off
	switch (c) {
		case '(': return Token(TOKEN_LEFT_PAREN, start, current - start, line);
		case ')': return Token(TOKEN_RIGHT_PAREN, start, current - start, line);
		case '{': return Token(TOKEN_LEFT_BRACE, start, current - start, line);
		case '}': return Token(TOKEN_RIGHT_BRACE, start, current - start, line);
		case ';': return Token(TOKEN_SEMICOLON, start, current - start, line);
		case ',': return Token(TOKEN_COMMA, start, current - start, line);
		case '.': return Token(TOKEN_DOT, start, current - start, line);
		case '-': return Token(TOKEN_MINUS, start, current - start, line);
		case '+': return Token(TOKEN_PLUS, start, current - start, line);
		case '/': return Token(TOKEN_SLASH, start, current - start, line);
		case '*': return Token(TOKEN_STAR, start, current - start, line);
		case '!':
			return Token(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG, start, current - start, line);
		case '=':
			return Token(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL, start, current - start, line);
		case '<':
			return Token(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS, start, current - start, line);
		case '>':
			return Token(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER, start, current - start, line);
	}
	// clang-format on

	return ErrorToken("Unexpected character", line);
}

bool Scanner::match(char expected) {
	if (*current == '\0') return false;
	if (*current != expected) return false;
	current++;
	return true;
}

void Scanner::skipWhitespace() {
	while (true) {
		char c = *current;
		switch (c) {
			case ' ':
			case '\r':
			case '\t':
				current++;
				break;
			case '\n':
				line++;
				current++;
				break;
			case '/':
				if (current[1] == '/')
					// advance until end of line
					while (*current != '\n' || '\0')
						current++;
			default:
				return;
		}
	}
}
