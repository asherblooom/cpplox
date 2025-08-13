#include "debug.hpp"

#include <iostream>
#include <string>
#include "chunk.hpp"

static int simpleInstruction(std::string opcode, int offset);

void dissassembleChunk(Chunk& chunk, std::string name) {
	std::cout << "== " << name << " ==\n";
	for (size_t offset = 0; offset < chunk.Code.size();) {
		// we leave incrememnting offset to the ...Instruction functions
		// as instructions can have different sizes
		offset = dissassembleInstruction(chunk, offset);
	}
}

int dissassembleInstruction(Chunk& chunk, int offset) {
	printf("%04d ", offset);  // print with leading 0's
	unsigned char instruction = chunk.Code.at(offset);
	switch (instruction) {
		case OP_RETURN:
			return simpleInstruction("OP_RETURN", offset);
		default:
			std::cerr << "Unknown opcode " << instruction << "\n";
			return offset + 1;
	}
}

static int simpleInstruction(std::string opcode, int offset) {
	std::cout << opcode << "\n";
	return offset + 1;
}
