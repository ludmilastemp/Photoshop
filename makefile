default: test

OPTIMIZE_LEVEL = -O3 #-O0

CXX = g++
CXX_FLAGS = -g $(OPTIMIZE_LEVEL) -I .
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system 
BUILD_DIR = ./build
BIN = photoshop

CPP_SRC = 																	\
	main.cpp 																\
	GrLib/color.cpp GrLib/GrLib.cpp 										\
	MVC/controllerPhotoshop.cpp MVC/modelCanvas.cpp MVC/viewPhotoshop.cpp 	\
	MVC/Controller/modelButton.cpp 											\
	MVC/Managers/actions.cpp MVC/Managers/toolbar.cpp 						\
	MVC/BaseSettings/create.cpp 											\
	objects/button.cpp objects/picture.cpp 									\
	Standard/PsSPI-impl.cpp 												\
	vectors/vectorDec.cpp
# main.cpp $(wildcard */*.cpp) $(wildcard */*/*.cpp) $(wildcard */*/*/*.cpp)

SO_SRC = $(wildcard plugins/*.cpp) $(wildcard filters/*.cpp)
OBJ = $(CPP_SRC:%.cpp=$(BUILD_DIR)/%.o) 
SO  = $(SO_SRC:%.cpp=$(BUILD_DIR)/%.so) 
DEPFILES = $(OBJ:%.o=%.d) $(SO:%.so=%.d)

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

$(BUILD_DIR)/%.so : %.cpp
	mkdir -p $(@D)
	mkdir -p so/
	$(CXX) $< $(CXX_FLAGS) -MMD -shared -fPIC -o $@
	cp $@ so/

$(BUILD_DIR)/$(BIN) : $(OBJ) $(SO)
	mkdir -p $(@D)
	$(CXX) $^ $(CXX_FLAGS) $(SFML_FLAGS) -o $@

test: $(BUILD_DIR)/$(BIN)
	$(BUILD_DIR)/$(BIN) $(SO)

clean:
	rm -rf .depend build so

.PHONY: run

sinclude .depend
