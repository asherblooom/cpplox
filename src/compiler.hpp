#ifndef COMPILER_HPP
#define COMPILER_HPP

#include <initializer_list>
#include <string>
#include "chunk.hpp"
#include "scanner.hpp"
#include "token.hpp"

enum Precedence {
	PREC_NONE,
	PREC_ASSIGNMENT,  // =
	PREC_OR,		  // or
	PREC_AND,		  // and
	PREC_EQUALITY,	  // == !=
	PREC_COMPARISON,  // < > <= >=
	PREC_TERM,		  // + -
	PREC_FACTOR,	  // * /
	PREC_UNARY,		  // ! -
	PREC_CALL,		  // . ()
	PREC_PRIMARY
};

class Parser {
public:
	bool HadError;
	Token Previous;
	Token Current;
	Parser(std::string src);
	void SetSource(std::string src);

	void Advance();
	void AdvanceIfType(TokenType type, const char* message);

private:
	Scanner scanner;
	bool panicMode;
	void errorAt(Token& token, const char* message);
};

class Compiler {
public:
	bool Compile(std::string src, Chunk& chunk);

private:
	Chunk* compilingChunk;
	Parser parser = Parser("");

	void writeBytes(std::initializer_list<unsigned char> bytes);
	Chunk* currentChunk() { return compilingChunk; }
	void endCompiler() { writeBytes({OP_RETURN}); }

	void expression();
	void number();
	void grouping();
	void unary();
	void parsePrecedence(Precedence precedence);
};

#endif
