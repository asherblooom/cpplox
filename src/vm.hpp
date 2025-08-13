#ifndef VM_HPP
#define VM_HPP

#include "chunk.hpp"

enum InterpretResult {
	INTERPRET_OK,
	INTERPRET_COMPILE_ERROR,
	INTERPRET_RUNTIME_ERROR,
};

class VirtualMachine {
public:
	Chunk* CurrentChunk;
	std::vector<unsigned char>::iterator IP;

	InterpretResult Interpret(Chunk& chunk);

private:
	InterpretResult run();
};

#endif
