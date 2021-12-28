
# Compiler to use
COMPILER := g++

# Executable name
OUT_NAME := tac-runner

# Compiled files
FILES := src/*.cpp

# C++ Version
CPP_VERSION := c++17

# Compilation flags
CFLAGS := -pedantic -Wall

all: parsing	
	$(COMPILER) -o $(OUT_NAME) $(FILES) -std=$(CPP_VERSION) $(CFLAGS)

debug: parsing
	$(COMPILER) -o $(OUT_NAME) $(FILES) -std=$(CPP_VERSION) $(CFLAGS) -g -fdiagnostics-color=always
	
parsing:
	flex src/lexer.l
	bison src/parser.y
	mv _Parser.* _Lexer.* src

clean:
	rm src/_Parser.* src/_Lexer.* stack.hh $(OUT_NAME)