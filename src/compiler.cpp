#include "compiler.hpp"
#include <initializer_list>
#include "chunk.hpp"

bool Compiler::Compile(std::string src, Chunk& chunk) {
	parser.SetSource(src);
	compilingChunk = &chunk;
	parser.Advance();
	expression();
	parser.AdvanceIfType(TOKEN_EOF, "Expect end of expression");
	endCompiler();
	return !parser.HadError;
}

void Compiler::writeBytes(std::initializer_list<unsigned char> bytes) {
	for (auto byte : bytes)
		currentChunk()->Write(byte, parser.Previous.Line);
}

void Compiler::expression() {
	parsePrecedence(PREC_ASSIGNMENT);
}
void Compiler::number() {
	double value = strtod(parser.Previous.Start, nullptr);
	currentChunk()->WriteConstant(value, parser.Previous.Line);
}
void Compiler::grouping() {
	expression();
	parser.AdvanceIfType(TOKEN_RIGHT_PAREN, "Expect ')' after expression");
}
void Compiler::unary() {
	TokenType operatorType = parser.Previous.Type;
	// compile the operand
	parsePrecedence(PREC_UNARY);

	// write the operator instruction
	switch (operatorType) {
		case TOKEN_MINUS:
			writeBytes({OP_NEGATE});
			break;
		default:
			return;
	}
}

Parser::Parser(std::string src)
	: HadError{false},
	  Previous{TOKEN_ERROR, nullptr, 0, 0},
	  Current{TOKEN_ERROR, nullptr, 0, 0},
	  scanner{src},
	  panicMode{false} {}

void Parser::SetSource(std::string src) {
	scanner = Scanner(src);
}

void Parser::Advance() {
	Previous = Current;
	while (true) {
		Current = scanner.ScanToken();
		if (Current.Type == TOKEN_ERROR)
			errorAt(Current, Current.Start);
		else
			break;
	}
}

void Parser::AdvanceIfType(TokenType type, const char* errMessage) {
	if (Current.Type == type)
		Advance();
	else
		errorAt(Current, errMessage);
}

void Parser::errorAt(Token& token, const char* message) {
	if (panicMode) return;
	panicMode = true;
	fprintf(stderr, "[line %d] Error", token.Line);

	if (token.Type == TOKEN_EOF) {
		fprintf(stderr, " at end");
	} else if (token.Type == TOKEN_ERROR) {
		// Nothing.
	} else {
		fprintf(stderr, " at '%.*s'", token.Length, token.Start);
	}

	fprintf(stderr, ": %s\n", message);
	HadError = true;
}
