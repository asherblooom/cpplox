#include "debug.hpp"

#include <iostream>
#include <string>
#include "chunk.hpp"

static int simpleInstruction(std::string opcode, int offset);
static int constantInstruction(std::string opcode, Chunk& chunk, int offset);

void dissassembleChunk(Chunk& chunk, std::string name) {
	std::cout << "== " << name << " ==\n";
	std::cout << "offset  line  opcode           conOff  conVal\n";
	for (size_t offset = 0; offset < chunk.Size();) {
		// we leave incrememnting offset to the ...Instruction functions
		// as instructions can have different sizes
		offset = dissassembleInstruction(chunk, offset);
	}
}

int dissassembleInstruction(Chunk& chunk, int offset) {
	printf("%04d   ", offset);	// print with leading 0's

	if (offset > 0 && chunk.GetLine(offset) == chunk.GetLine(offset - 1))
		std::cout << "   |   ";
	else
		printf("%4d   ", chunk.GetLine(offset));

	unsigned char instruction = chunk[offset];
	switch (instruction) {
		case OP_RETURN:
			return simpleInstruction("OP_RETURN", offset);
		case OP_CONSTANT:
			return constantInstruction("OP_CONSTANT", chunk, offset);
		default:
			std::cerr << "ERROR: Unknown opcode " << (unsigned int)instruction << "\n";
			return offset + 1;
	}
}

static int simpleInstruction(std::string opcode, int offset) {
	std::cout << opcode << "\n";
	return offset + 1;
}

static int constantInstruction(std::string opcode, Chunk& chunk, int offset) {
	unsigned char constantLoc = chunk[offset + 1];
	printf("%-16s %04d    '", opcode.c_str(), constantLoc);
	std::cout << chunk.GetConstant(constantLoc) << "'\n";
	return offset + 2;
}
