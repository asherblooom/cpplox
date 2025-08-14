#include "chunk.hpp"
#include "vm.hpp"

int main(int argc, char *argv[]) {
	Chunk chunk;

	chunk.WriteConstant(1.2, 2);
	chunk.WriteConstant(3.4, 123);

	chunk.Write(OP_ADD, 123);

	chunk.WriteConstant(5.6, 123);

	chunk.Write(OP_DIVIDE, 123);
	chunk.Write(OP_NEGATE, 3);
	chunk.Write(OP_RETURN, 3);

	VirtualMachine vm;
	vm.Interpret(chunk);

	return 0;
}
