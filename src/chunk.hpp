#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <vector>
#include "value.hpp"

enum OpCode {
	OP_CONSTANT,
	OP_RETURN,
};

class Chunk {
public:
	// functions for accessing Code vector
	void Write(unsigned char byte, int line) {
		Code.push_back(byte);
		Lines.push_back(line);
	}
	size_t Size() { return Code.size(); }
	unsigned char operator[](int i) { return Code.at(i); }

	// functions for accessing Constants vector
	int AddConstant(Value constant) {
		Constants.push_back(constant);
		return Constants.back() - 1;
	}
	Value GetConstant(int i) { return Constants.at(i); }

	// functions for accessing Lines vector
	int GetLine(int i) { return Lines.at(i); }

private:
	std::vector<unsigned char> Code;
	std::vector<Value> Constants;
	std::vector<int> Lines;
};

#endif
