#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <vector>
#include "value.hpp"

enum OpCode {
	OP_CONSTANT,
	OP_CONSTANT_LONG,
	OP_NEGATE,
	OP_ADD,
	OP_SUBTRACT,
	OP_MULTIPLY,
	OP_DIVIDE,
	OP_RETURN,
};

struct Line {
	int LineNumber;
	int Count;
};

class Chunk {
public:
	// functions for accessing code vector
	void Write(unsigned char byte, int line);
	void WriteConstant(Value value, int line);
	size_t size();
	unsigned char& operator[](int i);

	// functions for accessing constants vector
	Value& GetConstant(int i);

	// functions for accessing lines vector
	int& GetLine(int i);

private:
	std::vector<unsigned char> code;
	std::vector<Value> constants;
	std::vector<Line> lines;
};

#endif
