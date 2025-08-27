#ifndef COMPILER_HPP
#define COMPILER_HPP

#include <array>
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
class Compiler;

typedef void (Compiler::*ParseFn)();
struct ParseRule {
	ParseFn prefix;
	ParseFn infix;
	Precedence precedence;
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
	void binary();
	void parsePrecedence(Precedence precedence);

	static constexpr std::array<ParseRule, 30> makeParseRules() {
		std::array<ParseRule, 30> res{};
		// clang-format off
		res[TOKEN_LEFT_PAREN]    = {&Compiler::grouping, NULL,              PREC_NONE},
		res[TOKEN_RIGHT_PAREN]   = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_LEFT_BRACE]    = {NULL,                NULL,              PREC_NONE}, 
		res[TOKEN_RIGHT_BRACE]   = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_COMMA]         = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_DOT]           = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_MINUS]         = {&Compiler::unary,    &Compiler::binary, PREC_TERM},
		res[TOKEN_PLUS]          = {NULL,                &Compiler::binary, PREC_TERM},
		res[TOKEN_SEMICOLON]     = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_SLASH]         = {NULL,                &Compiler::binary, PREC_FACTOR},
		res[TOKEN_STAR]          = {NULL,                &Compiler::binary, PREC_FACTOR},
		res[TOKEN_BANG]          = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_BANG_EQUAL]    = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_EQUAL]         = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_EQUAL_EQUAL]   = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_GREATER]       = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_GREATER_EQUAL] = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_LESS]          = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_LESS_EQUAL]    = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_IDENTIFIER]    = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_STRING]        = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_NUMBER]        = {&Compiler::number,   NULL,              PREC_NONE},
		res[TOKEN_AND]           = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_CLASS]         = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_ELSE]          = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_FALSE]         = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_FOR]           = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_FUN]           = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_IF]            = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_NIL]           = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_OR]            = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_PRINT]         = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_RETURN]        = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_SUPER]         = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_THIS]          = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_TRUE]          = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_VAR]           = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_WHILE]         = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_ERROR]         = {NULL,                NULL,              PREC_NONE},
		res[TOKEN_EOF]           = {NULL,                NULL,              PREC_NONE};
		// clang-format on
		return res;
	}
	static constexpr std::array<ParseRule, 30> rules = makeParseRules();
};

#endif
