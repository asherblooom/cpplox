#ifndef VM_HPP
#define VM_HPP

#include <string>
#include "chunk.hpp"

enum InterpretResult {
	INTERPRET_OK,
	INTERPRET_COMPILE_ERROR,
	INTERPRET_RUNTIME_ERROR,
};

class VirtualMachine {
public:
	Chunk* CurrentChunk;
	unsigned char* IP;

	std::vector<Value> Stack;
	Value* StackTop() { return &Stack.back() + 1; };
	Value StackPop() {
		Value val = Stack.back();
		Stack.pop_back();
		return val;
	}

	InterpretResult Interpret(std::string source);

private:
	InterpretResult run();

	template <class Func>
	void binaryOp(Func func);
};

#endif
