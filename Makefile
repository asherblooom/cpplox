TARGET_EXEC := compiler
CXX:=g++
CXXFLAGS:=-I$(INC_DIR) -march=native -Wall -Wextra -Wno-unused-parameter -std=c++20 
OBJ_DIR:=./obj
SRC_DIR:=./src

# Find all the C++ files we want to compile
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
# get a list of object files we want to compile by removing the 
# paths from the source files and then substituing .cpp for .o
_OBJS := $(patsubst %.cpp,%.o,$(notdir $(SRCS)))
# add the object directory to the front of the object files
OBJS := $(_OBJS:%=$(OBJ_DIR)/%)


.PHONY: main

main: obj $(TARGET_EXEC)

$(TARGET_EXEC): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -o $@ $< $(CXXFLAGS) -c

obj: 
	mkdir -p obj


.PHONY: clean

# remove object dir and target exec
clean:
	rm -rf $(OBJ_DIR) $(TARGET_EXEC)



