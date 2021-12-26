
# Compiler to use
COMPILER := g++

# Executable name
OUT_NAME := tac-runner

# Compiled files
FILES := src/*.cpp

all: parsing	
	$(COMPILER) -o $(OUT_NAME) $(FILES)

parsing:
	flex src/lexer.l
	bison src/parser.y
	mv _Parser.* _Lexer.* src

clean:
	rm src/_Parser.* src/_Lexer.* stack.hh $(OUT_NAME)