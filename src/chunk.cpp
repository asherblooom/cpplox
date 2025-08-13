#include "chunk.hpp"

void Chunk::Write(unsigned char byte, int line) {
	Code.push_back(byte);
	int size = Lines.size() - 1;
	if (size != -1 && Lines.at(size).LineNumber == line) {
		Lines.at(size).Count += 1;
	} else {
		Lines.push_back({line, 1});
	}
}
size_t Chunk::Size() { return Code.size(); }
unsigned char Chunk::operator[](int i) { return Code.at(i); }

int Chunk::AddConstant(Value constant) {
	Constants.push_back(constant);
	return Constants.size() - 1;
}
Value Chunk::GetConstant(int i) { return Constants.at(i); }

int Chunk::GetLine(int instructionIndex) {
	int j = 0;
	int lineIndex = 0;
	while (true) {
		Line currLine = Lines.at(lineIndex);
		// increment j currline.Count times or until it is at correct instruction
		for (int k = 0; k < currLine.Count; k++) {
			if (j == instructionIndex) goto endloop;
			j++;
		}
		lineIndex++;
	}
endloop:
	return Lines.at(lineIndex).LineNumber;
}
