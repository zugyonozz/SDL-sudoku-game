CC = gcc
CXX = g++
CFLAGS = -Wall -Iinclude
CXXFLAGS = $(CFLAGS)
LDFLAGS = -Llib -lSDL2 -lSDL2_image -lSDL2_ttf -mconsole

SRC_C = src/sudoku_logic.c
SRC_CPP = src/main.cpp src/sudoku_gui.cpp
OBJ_C = $(SRC_C:.c=.o)
OBJ_CPP = $(SRC_CPP:.cpp=.o)

BIN = bin/main.exe

all: $(BIN)

# Kompilasi file C
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Kompilasi file C++
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link semua object files
$(BIN): $(OBJ_C) $(OBJ_CPP)
	$(CXX) $(OBJ_C) $(OBJ_CPP) -o $(BIN) $(LDFLAGS)

run: $(BIN)
	./$(BIN)

clean:
	rm -f src/*.o bin/main.exe
