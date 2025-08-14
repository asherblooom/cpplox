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

	std::vector<Value> Stack;
	std::vector<Value>::iterator StackTop() { return Stack.end(); };
	Value StackPop() {
		Value val = Stack.back();
		Stack.pop_back();
		return val;
	}

	InterpretResult Interpret(Chunk& chunk);

private:
	InterpretResult run();

	template <class Func>
	void binaryOp(Func func);
};

#endif
