#include "chunk.hpp"
#include "vm.hpp"

int main(int argc, char *argv[]) {
	Chunk chunk;

	chunk.WriteConstant(1, 1);
	chunk.WriteConstant(1.2, 2);
	chunk.Write(OP_RETURN, 3);

	VirtualMachine vm;
	vm.Interpret(chunk);

	return 0;
}
