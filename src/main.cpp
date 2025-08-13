#include "chunk.hpp"
#include "debug.hpp"
#include "vm.hpp"

int main(int argc, char *argv[]) {
	Chunk chunk;

	for (int i = 0; i < 260; i++) {
		chunk.WriteConstant(1.2, 123);
	}

	chunk.Write(OP_RETURN, 123);

	// dissassembleChunk(chunk, "chunky");
	VirtualMachine vm;
	vm.Interpret(chunk);
	return 0;
}
