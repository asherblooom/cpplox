#include "debug.hpp"

#include <iostream>
#include <string>
#include "chunk.hpp"

static int simpleInstruction(std::string opcode, int offset);
static int constantInstruction(std::string opcode, Chunk& chunk, int offset);
static int longConstantInstruction(std::string opcode, Chunk& chunk, int offset);

void dissassembleChunk(Chunk& chunk, std::string name) {
	std::cout << "== " << name << " ==\n";
	std::cout << "offset  line  opcode           constOff  constVal\n";
	for (size_t offset = 0; offset < chunk.size();) {
		// we leave incrememnting offset to the ...Instruction functions
		// as instructions can have different sizes
		offset = dissassembleInstruction(chunk, offset);
	}
	std::cout << "\n";
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
		case OP_CONSTANT_LONG:
			return longConstantInstruction("OP_CONSTANT_LONG", chunk, offset);
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
	printf("%-16s %03d       '", opcode.c_str(), constantLoc);
	std::cout << chunk.GetConstant(constantLoc) << "'\n";
	return offset + 2;
}

static int longConstantInstruction(std::string opcode, Chunk& chunk, int offset) {
	unsigned long constantLoc = ((unsigned long)chunk[offset + 1]) << 8 | ((unsigned long)chunk[offset + 2] << 4) | chunk[offset + 3];
	printf("%-16s %08lu  '", opcode.c_str(), constantLoc);
	std::cout << chunk.GetConstant(constantLoc) << "'\n";
	return offset + 4;
}
