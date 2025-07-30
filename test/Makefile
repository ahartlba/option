# Makefile to compile main.cc

# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -Wall -Wextra -std=c++11

# Target executable
TARGET := tests

# Source files
SRC := tests.cc

# Build rules
all: run

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
