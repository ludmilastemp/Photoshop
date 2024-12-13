default: test

OPTIMIZE_LEVEL = #-O0

CXX = g++
CXX_FLAGS = -g $(OPTIMIZE_LEVEL)
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system 
BUILD_DIR = ./build
BIN = photoshop

CPP_SRC=main.cpp $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp)
OBJ = $(CPP_SRC:%.cpp=$(BUILD_DIR)/%.o) 
DEPFILES = $(OBJ:%.o=%.d)

depend: .depend

%.d : %.cpp
	rm -f "$@"
	$(CXX) $^ $(CXX_FLAGS) -MM -MF "$@"

.depend : $(DEPFILES)
	echo $(DEPFILES)
	cat $^ > "$@"

$(BUILD_DIR)/%.o : %.cpp
	mkdir -p $(@D)
	$(CXX) $< $(CXX_FLAGS) -MMD -c -o $@

$(BUILD_DIR)/$(BIN) : $(OBJ)
	mkdir -p $(@D)
	$(CXX) $^ $(CXX_FLAGS) $(SFML_FLAGS) -o $@

test: $(BUILD_DIR)/$(BIN)
	$(BUILD_DIR)/$(BIN)

clean:
	rm -rf .depend build

.PHONY: run

sinclude .depend
