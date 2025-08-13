#include "vm.hpp"
#include <iostream>

#define READ_BYTE() (*IP++)
#define READ_CONSTANT() (CurrentChunk->GetConstant(READ_BYTE()))

InterpretResult VirtualMachine::Interpret(Chunk& chunk) {
	CurrentChunk = &chunk;
	IP = chunk.begin();
	return run();
}

InterpretResult VirtualMachine::run() {
	while (IP != CurrentChunk->end()) {
		unsigned char instruction;
		switch (instruction = READ_BYTE()) {
			case OP_CONSTANT: {
				Value constant = READ_CONSTANT();
				std::cout << constant << "\n";
				break;
			}
			case OP_RETURN: {
				return INTERPRET_OK;
			}
		}
	}
}

#undef READ_BYTE
#undef READ_CONSTANT
