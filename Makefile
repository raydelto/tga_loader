CXX=g++
CXXFLAGS := -Wall -std=c++17 -DSDL_MAIN_HANDLED $(shell sdl2-config --cflags)
LDFLAGS := $(shell sdl2-config --libs)

SRC=src/tga_loader.cpp \
    src/graphics.cpp

OBJ=bin/tga_loader.o \
    bin/graphics.o

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    LIBS = -lSDL2
    INCLUDES = -I /usr/include
else ifeq ($(UNAME_S),Darwin)
    LIBS = -L/opt/homebrew/opt/sdl2/lib -lsdl2
    INCLUDES = -I/opt/homebrew/opt/sdl2/include -I/usr/local/include
else
    # Configuración para Windows (MinGW-w64 en MSYS2)
    LIBS = -lmingw32 -lSDL2main -lSDL2
    INCLUDES =
endif

WARNINGS=-Wall
CPP_VERSION=-std=c++17

all: bin $(OBJ)
	$(CXX) -g src/main.cpp $(OBJ) $(LIBS) $(INCLUDES) -o ./main $(WARNINGS) $(CPP_VERSION) $(LDFLAGS)

bin:
	mkdir -p bin

bin/%.o: src/%.cpp
	$(CXX) -g -c $< -o $@ $(CXXFLAGS)

clean:
	rm -rf bin/*.o bin/main
