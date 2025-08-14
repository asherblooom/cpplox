#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <string>
#include "chunk.hpp"
#include "value.hpp"

void dissassembleChunk(Chunk& chunk, std::string name);
int dissassembleInstruction(Chunk& chunk, int offset);
void outputStack(std::vector<Value>& stack);

#endif
