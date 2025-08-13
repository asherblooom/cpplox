#include "vm.hpp"
#include <iostream>
#include "common.h"
#include "debug.hpp"

#define READ_BYTE() (*IP++)
#define READ_CONSTANT() (CurrentChunk->GetConstant(READ_BYTE()))

InterpretResult VirtualMachine::Interpret(Chunk& chunk) {
	CurrentChunk = &chunk;
	IP = chunk.begin();

#ifdef DEBUG_TRACE_EXECUTION
	std::cout << "offset  line  opcode           constOff  constVal\n";
#endif

	return run();
}

InterpretResult VirtualMachine::run() {
	while (IP != CurrentChunk->end()) {
#ifdef DEBUG_TRACE_EXECUTION
		dissassembleInstruction(*CurrentChunk, (int)(IP - CurrentChunk->begin()));
#endif
		unsigned char instruction;
		switch (instruction = READ_BYTE()) {
			case OP_CONSTANT: {
				Value constant = READ_CONSTANT();
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
