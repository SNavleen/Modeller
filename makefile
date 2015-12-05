LDFLAGS = -lGL -lGLU -lglut
CFLAGS=-g -Wall -std=c++11
CC=g++
EXEEXT=
RM=rm
PROGRAM_NAME= Modeller

# Windows (cygwin)
ifeq "$(OS)" "Windows_NT"
	EXEEXT=.exe #on windows applications must have .exe extension
	RM=del #rm command for windows powershell
    LDFLAGS = -lfreeglut -lglu32 -lopengl32
else
	# OS X
	OS := $(shell uname)
	ifeq ($(OS), Darwin)
	        LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT
	endif
endif

run: $(PROGRAM_NAME) clean

clean:
	$(RM) *.o $(PROGRAM_NAME)$(EXEEXT)

$(PROGRAM_NAME): Modeller.o Window.o DrawShape.o node.o nodeGroup.o nodeTransform.o sceneGraph.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	./$(PROGRAM_NAME)$(EXEEXT)
