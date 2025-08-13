#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <string>
#include "chunk.hpp"

void dissassembleChunk(Chunk& chunk, std::string name);
int dissassembleInstruction(Chunk& chunk, int offset);

#endif
