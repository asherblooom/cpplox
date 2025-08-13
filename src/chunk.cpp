#include "chunk.hpp"

void Chunk::Write(unsigned char byte, int line) {
	Code.push_back(byte);
	Lines.push_back(line);
}
size_t Chunk::Size() { return Code.size(); }
unsigned char Chunk::operator[](int i) { return Code.at(i); }

int Chunk::AddConstant(Value constant) {
	Constants.push_back(constant);
	return Constants.back() - 1;
}
Value Chunk::GetConstant(int i) { return Constants.at(i); }

int Chunk::GetLine(int i) { return Lines.at(i); }
