#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <vector>

enum OpCode {
	OP_RETURN,
};

class Chunk {
public:
	std::vector<unsigned char> Code;
};

#endif
