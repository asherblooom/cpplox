#include "vm.hpp"
#include <iostream>
#include "common.hpp"
#include "compiler.hpp"
#include "debug.hpp"

#define READ_BYTE() (*IP++)
#define READ_CONSTANT() (CurrentChunk->GetConstant(READ_BYTE()))

InterpretResult VirtualMachine::Interpret(std::string source) {
	Chunk chunk;
	Compiler compiler;
	if (!compiler.Compile(source, chunk))
		return INTERPRET_COMPILE_ERROR;

	this->CurrentChunk = &chunk;
	this->IP = &(*this->CurrentChunk)[0];
	InterpretResult result = run();
	return result;
}

InterpretResult VirtualMachine::run() {
#ifdef DEBUG_TRACE_EXECUTION
	std::cout << "offset  line  opcode           constOff  constVal\n";
#endif
	unsigned char end = (*CurrentChunk)[CurrentChunk->size() - 1] + 1;
	while (IP != &end) {
#ifdef DEBUG_TRACE_EXECUTION
		outputStack(Stack);
		dissassembleInstruction(*CurrentChunk, (int)(IP - &(*CurrentChunk)[0]));
#endif
		unsigned char instruction;
		switch (instruction = READ_BYTE()) {
			case OP_CONSTANT: {
				Value constant = READ_CONSTANT();
				Stack.push_back(constant);
				break;
			}
			case OP_NEGATE: {
				Value& a = Stack.back();
				a = -a;
				break;
			}
			case OP_ADD: {
				binaryOp(std::plus());
				break;
			}
			case OP_SUBTRACT: {
				binaryOp(std::minus());
				break;
			}
			case OP_MULTIPLY: {
				binaryOp(std::multiplies());
				break;
			}
			case OP_DIVIDE: {
				binaryOp(std::divides());
				break;
			}
			case OP_RETURN: {
				std::cout << StackPop() << "\n";
				return INTERPRET_OK;
			}
		}
	}
	return INTERPRET_RUNTIME_ERROR;
}

template <class Func>
void VirtualMachine::binaryOp(Func func) {
	Value b = StackPop();
	Value& a = Stack.back();
	a = func(a, b);
}

#undef READ_BYTE
#undef READ_CONSTANT
