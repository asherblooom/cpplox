#include "scanner.hpp"
#include "token.hpp"

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

	if (c >= '0' && c <= '9')
		return number();
	else if ((c >= 'a' && c <= 'z') ||
			 (c >= 'A' && c <= 'Z') ||
			 (c == '_'))
		return identifier();
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
		case '"': return string();
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

Token Scanner::string() {
	while (true) {
		char c = *current;
		switch (c) {
			case '"':
				current++;
				return Token(TOKEN_STRING, start, current - start, line);
			case '\n':
				line++;
				current++;
			case '\0':
				return ErrorToken("Unterminated string", line);
			default:
				current++;
		}
	}
}

Token Scanner::number() {
	while (true) {
		char c = *current;
		char next = current[1];
		if (c >= '0' && c <= '9')
			current++;
		else if (c == '.' && (next >= '0' && next <= '9'))
			current++;
		else {
			current++;
			return Token(TOKEN_NUMBER, start, current - start, line);
		}
	}
}

Token Scanner::identifier() {
	while (true) {
		char c = *current;
		if ((c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') ||
			(c == '_'))
			current++;
		else if (c >= '0' && c <= '9')
			current++;
		else {
			current++;
			return Token(TOKEN_IDENTIFIER, start, current - start, line);
		}
	}
}

TokenType Scanner::identifierType() {
	// clang-format off
	switch(*start){
		case 'a': return checkKeyword(1, 2, "nd", TOKEN_AND);
		case 'c': return checkKeyword(1, 4, "lass", TOKEN_CLASS);
		case 'e': return checkKeyword(1, 3, "lse", TOKEN_ELSE);
		case 'f':
			if (current - start > 1) {
				switch (start[1]) {
					case 'a': return checkKeyword(2, 3, "lse", TOKEN_FALSE);
					case 'o': return checkKeyword(2, 1, "r", TOKEN_FOR);
					case 'u': return checkKeyword(2, 1, "n", TOKEN_FUN);
				}
			} else return TOKEN_IDENTIFIER;
		case 'i': return checkKeyword(1, 1, "f", TOKEN_IF);
		case 'n': return checkKeyword(1, 2, "il", TOKEN_NIL);
		case 'o': return checkKeyword(1, 1, "r", TOKEN_OR);
		case 'p': return checkKeyword(1, 4, "rint", TOKEN_PRINT);
		case 'r': return checkKeyword(1, 5, "eturn", TOKEN_RETURN);
		case 's': return checkKeyword(1, 4, "uper", TOKEN_SUPER);
		case 't':
			if (current - start > 1) {
				switch (start[1]) {
					case 'h': return checkKeyword(2, 2, "is", TOKEN_THIS);
					case 'r': return checkKeyword(2, 2, "ue", TOKEN_TRUE);
				}
			} else return TOKEN_IDENTIFIER;
		case 'v': return checkKeyword(1, 2, "ar", TOKEN_VAR);
		case 'w': return checkKeyword(1, 4, "hile", TOKEN_WHILE);
		default: return TOKEN_IDENTIFIER;
	}
	// clang-format on
}

TokenType Scanner::checkKeyword(int offset, int restLength, const char* rest, TokenType type) {
	if (current - start == offset + restLength &&
		memcmp(start + offset, rest, restLength) == 0) {
		return type;
	} else
		return TOKEN_IDENTIFIER;
}
