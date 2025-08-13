#include "chunk.hpp"
#include "debug.hpp"

int main(int argc, char *argv[]) {
	Chunk chunk;

	int i = chunk.AddConstant(1.2);
	chunk.Write(OP_CONSTANT, 123);
	chunk.Write(i, 123);

	chunk.Write(OP_RETURN, 123);

	dissassembleChunk(chunk, "chunky");
	return 0;
}
