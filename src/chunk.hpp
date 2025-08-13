#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <vector>
#include "value.hpp"

enum OpCode {
	OP_CONSTANT,
	OP_RETURN,
};

struct Line {
	int LineNumber;
	int Count;
};

class Chunk {
public:
	// functions for accessing Code vector
	void Write(unsigned char byte, int line);
	size_t Size();
	unsigned char operator[](int i);

	// functions for accessing Constants vector
	int AddConstant(Value constant);
	Value GetConstant(int i);

	// functions for accessing Lines vector
	int GetLine(int i);

private:
	std::vector<unsigned char> Code;
	std::vector<Value> Constants;
	std::vector<Line> Lines;
};

#endif
