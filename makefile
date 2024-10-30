a.out: tmp/main.o		                \
		tmp/GrLib/GrLib.o                 \
		tmp/GrLib/color.o                 \
		tmp/MVC/controllerPhotoshop.o     \
		tmp/MVC/modelPhotoshop.o          \
		tmp/MVC/viewPhotoshop.o           \
		tmp/MVC/MVC_Button/modelButton.o  \
		tmp/objects/button.o              \
		tmp/objects/picture.o             \
		tmp/vectors/vectorDec.o           \

	g++ tmp/main.o		                \
		tmp/GrLib/GrLib.o                 \
		tmp/GrLib/color.o                 \
		tmp/MVC/controllerPhotoshop.o     \
		tmp/MVC/modelPhotoshop.o          \
		tmp/MVC/viewPhotoshop.o           \
		tmp/MVC/MVC_Button/modelButton.o  \
		tmp/objects/button.o              \
		tmp/objects/picture.o             \
		tmp/vectors/vectorDec.o           \
		-lsfml-graphics -lsfml-window -lsfml-system \

tmp/main.o: main.cpp \
		GrLib/GrLib.hpp \
		MVC/controllerPhotoshop.hpp \
		MVC/modelPhotoshop.hpp \
		MVC/viewPhotoshop.hpp \
		tools/brush.hpp \
		tools/eraser.hpp \
		tools/line.hpp 
	g++ -c main.cpp -o tmp/main.o

tmp/GrLib/GrLib.o: GrLib/GrLib.cpp \
		GrLib/GrLib.hpp \
		GrLib/GrLibCtx.hpp \
		vectors/vectorDec.hpp 
	g++ -c GrLib/GrLib.cpp -o tmp/GrLib/GrLib.o

tmp/GrLib/color.o: GrLib/color.cpp \
		GrLib/color.hpp 
	g++ -c GrLib/color.cpp -o tmp/GrLib/color.o

tmp/MVC/controllerPhotoshop.o: MVC/controllerPhotoshop.cpp \
		MVC/controllerPhotoshop.hpp \
		MVC/MVC_Button/modelButton.hpp \
		objects/button.hpp 
	g++ -c MVC/controllerPhotoshop.cpp -o tmp/MVC/controllerPhotoshop.o

tmp/MVC/modelPhotoshop.o: MVC/modelPhotoshop.cpp \
		MVC/modelPhotoshop.hpp \
		MVC/systemState.hpp \
		GrLib/GrLibCtx.hpp \
		objects/picture.hpp \
		GrLib/color.hpp \
		tools/tool.hpp \
		vectors/vectorDec.hpp \
		GrLib/GrLib.hpp 
	g++ -c MVC/modelPhotoshop.cpp -o tmp/MVC/modelPhotoshop.o

tmp/MVC/viewPhotoshop.o: MVC/viewPhotoshop.cpp \
		MVC/viewPhotoshop.hpp \
		MVC/systemState.hpp \
		GrLib/GrLibCtx.hpp \
		objects/picture.hpp \
		GrLib/GrLib.hpp 
	g++ -c MVC/viewPhotoshop.cpp -o tmp/MVC/viewPhotoshop.o

tmp/MVC/MVC_Button/modelButton.o: MVC/MVC_Button/modelButton.cpp \
		MVC/MVC_Button/modelButton.hpp \
		objects/button.hpp 
	g++ -c MVC/MVC_Button/modelButton.cpp -o tmp/MVC/MVC_Button/modelButton.o

tmp/objects/button.o: objects/button.cpp \
		objects/button.hpp \
		objects/object.hpp \
		GrLib/GrLibCtx.hpp \
		vectors/vectorDec.hpp \
		objects/actions.hpp \
		MVC/modelPhotoshop.hpp \
		MVC/systemState.hpp \
		GrLib/GrLibCtx.hpp \
		objects/picture.hpp \
		GrLib/GrLib.hpp \
		vectors/vectorDec.hpp \
		GrLib/color.hpp 
	g++ -c objects/button.cpp -o tmp/objects/button.o

tmp/objects/picture.o: objects/picture.cpp \
		objects/picture.hpp \
		objects/object.hpp \
		GrLib/GrLibCtx.hpp \
		vectors/vectorDec.hpp \
		GrLib/color.hpp 
	g++ -c objects/picture.cpp -o tmp/objects/picture.o

tmp/vectors/vectorDec.o: vectors/vectorDec.cpp \
		vectors/vectorDec.hpp 
	g++ -c vectors/vectorDec.cpp -o tmp/vectors/vectorDec.o

#g++ main.cpp		                \
		GrLib/GrLib.cpp                 \
		GrLib/color.cpp                 \
		MVC/controllerPhotoshop.cpp     \
		MVC/modelPhotoshop.cpp          \
		MVC/viewPhotoshop.cpp           \
		MVC/MVC_Button/modelButton.cpp  \
		MVC/MVC_Button/viewButton.cpp   \
		objects/button.cpp              \
		objects/picture.cpp             \
		vectors/vectorDec.cpp           \
		-lsfml-graphics -lsfml-window -lsfml-system \
\
\
g++ main.cpp GrLib/GrLib.cpp GrLib/color.cpp MVC/controllerPhotoshop.cpp MVC/modelPhotoshop.cpp MVC/viewPhotoshop.cpp MVC/MVC_Button/modelButton.cpp MVC/MVC_Button/viewButton.cpp objects/button.cpp objects/picture.cpp vectors/vectorDec.cpp -lsfml-graphics -lsfml-window -lsfml-system \
\
		\
		objects/molecule.cpp      		\
		objects/wall.cpp         		\
		\
		objects/scene.cpp       	\
		objects/button.cpp      	\
		objects/light.cpp       	\
		objects/lightManager.cpp	\
		vectors/vector3D.cpp 		\
		tests/testSimple2D.cpp  	\
		tests/testSimple3D.cpp  	\
		tests/testFollowMouse.cpp  	\
		tests/testButtonControl.cpp	\
		test.cpp    	        	\
		-Wno-narrowing          	\
		-Wno-unused-parameter		\
		-D _DEBUG -ggdb3 -Wall -Wextra -Waggressive-loop-optimizations -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 #-Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

# -Weffc++
# warning: ‘class Object’ has pointer data members [-Weffc++]

# -Wconversion 

# -Wshadow
# warning: declaration of ‘isDraw’ shadows a member of ‘Button’ [-Wshadow]
#   12 | Button::Button (bool isDraw, const VectorDec& init_corner, const VectorDec& init_size, const Color& init_color)

