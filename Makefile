CXX=g++
CXXFLAGS := -Wall -std=c++17 -DSDL_MAIN_HANDLED $(shell sdl2-config --cflags)
LDFLAGS := $(shell sdl2-config --libs)

SRC=src/tga_loader.cpp \
    src/graphics.cpp

OBJ=tga_loader.o \
	graphics.o

LIBS=-lSDL2

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LIBS += -L/usr/lib
	INCLUDES = -I/usr/include
	RM=rm -f
endif
ifeq ($(UNAME_S),Darwin)
	LIBS += -L/opt/homebrew/opt/sdl2/lib
	INCLUDES = -I/opt/homebrew/opt/sdl2/include \
		-I/usr/local/include
	RM=rm -f
endif
ifeq ($(OS),Windows_NT)
	LIBS += -LC:\msys64\mingw64\lib -lSDL2main
	INCLUDES = -IC:\msys64\mingw64\include
	RM=del /Q
endif

WARNINGS=-Wall
CPP_VERSION=-std=c++17

all:
	$(CXX) -g -c $(SRC) $(INCLUDES) $(WARNINGS) $(CPP_VERSION)  -mconsole
	$(CXX) -g src/main.cpp $(OBJ) $(LIBS) $(INCLUDES) -o bin/main $(WARNINGS) $(CPP_VERSION)  -mconsole

clean:
	$(RM) *.o
	$(RM) *.exe
	$(RM) -r bin
