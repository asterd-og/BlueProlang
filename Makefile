all:
	clang++ $(wildcard src/*.cpp src/lexer/*.cpp src/parser/*.cpp src/evaluator/*.cpp) -o out/blue
	out/blue test/prog1.blu