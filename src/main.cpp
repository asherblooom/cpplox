#include "chunk.hpp"
#include "debug.hpp"

int main(int argc, char *argv[]) {
	Chunk chunk;
	chunk.Code.push_back(OP_RETURN);
	dissassembleChunk(chunk, "chunky");
	return 0;
}
