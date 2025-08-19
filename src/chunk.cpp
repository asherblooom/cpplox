#include "chunk.hpp"
#include <climits>

void Chunk::Write(unsigned char byte, int line) {
	code.push_back(byte);
	int size = lines.size() - 1;
	if (size != -1 && lines.at(size).LineNumber == line) {
		lines.at(size).Count += 1;
	} else {
		lines.push_back({line, 1});
	}
}
void Chunk::WriteConstant(Value value, int line) {
	constants.push_back(value);
	int index = constants.size() - 1;
	if (index < UCHAR_MAX + 1) {
		Write(OP_CONSTANT, line);
		Write(index, line);
	} else {
		Write(OP_CONSTANT_LONG, line);
		Write((unsigned char)(index >> 8), line);
		Write((unsigned char)(index >> 4), line);
		Write((unsigned char)index, line);
	}
}

size_t Chunk::size() { return code.size(); }
unsigned char& Chunk::operator[](int i) { return code.at(i); }

Value& Chunk::GetConstant(int i) { return constants.at(i); }

int& Chunk::GetLine(int instructionIndex) {
	int j = 0;
	int lineIndex = 0;
	while (true) {
		Line currLine = lines.at(lineIndex);
		// increment j currline.Count times or until it is at correct instruction
		for (int k = 0; k < currLine.Count; k++) {
			if (j == instructionIndex) goto endloop;
			j++;
		}
		lineIndex++;
	}
endloop:
	return lines.at(lineIndex).LineNumber;
}
