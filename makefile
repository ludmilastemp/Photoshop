OPTIMIZE_LEVEL = #-O3

DIR = $(shell pwd)
CXX = g++
CXX_FLAGS = $(OPTIMIZE_LEVEL)
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system 
BUILD_DIR = ./build
BIN = photoshop

CPP_SRC=$(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp)
OBJ = $(CPP_SRC:%.cpp=$(BUILD_DIR)/%.o)
DEPFILES = $(OBJ:%.o=%.d)

$(BUILD_DIR)/%.o : %.cpp
	mkdir -p $(@D)
	$(CXX) $< $(CXX_FLAGS) -c -o $@

$(BUILD_DIR)/$(BIN) : $(OBJ)
	mkdir -p $(@D)
	$(CXX) $^ $(CXX_FLAGS) $(SFML_FLAGS) -o $@

clean:
	rm -rf build

.PHONY: run

