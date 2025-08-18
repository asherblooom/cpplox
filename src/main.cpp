#include <cstdlib>
#include <fstream>
#include <iostream>
#include "vm.hpp"

static void repl();
static void runFile(const std::string path);
static std::string readFile(const std::string path);

VirtualMachine vm;

int main(int argc, char* argv[]) {
	if (argc == 1) {
		repl();
	} else if (argc == 2) {
		runFile(argv[1]);
	} else {
		std::cerr << "Usage: clox [path]\n";
		std::exit(65);
	}
	return 0;
}

static void repl() {
	std::string line;
	std::cout << "> ";
	while (getline(std::cin, line, '\\')) {
		vm.Interpret(line);
		std::cout << "> ";
	}
	std::cout << "\n";
	return;
}

static void runFile(const std::string path) {
	std::string source = readFile(path);
	InterpretResult result = vm.Interpret(source);

	if (result == INTERPRET_COMPILE_ERROR) exit(65);
	if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

static std::string readFile(const std::string path) {
	std::ifstream file{path};
	if (!file) {
		std::cerr << "ERROR: Unable to open file: " << path << "\n";
		exit(74);
	}
	std::string contents;
	// move get position to end of file
	file.seekg(0, std::ios::end);
	// resize string with position of end of file (e.g. size of file)
	contents.resize(file.tellg());
	// reset to beginning
	file.seekg(0, std::ios::beg);
	file.read(&contents[0], contents.size());
	file.close();

	// TODO: is this needed?
	// contents.push_back('\0');
	return contents;
}
