CPPFLAGS += -std=c++11 -W -Wall -g -Wno-unused-parameter -Wno-reorder
CPPFLAGS += -I include

all : bin/Context.o bin/print_mips bin/c_compiler bin/eval_expr bin/print_py

bin/Context.o: include/Context.hpp include/Context.cpp
	mkdir -p bin
	g++ $(CPPFLAGS) -c include/Context.cpp -o bin/Context.o

src/maths_parser.tab.cpp src/maths_parser.tab.hpp : src/maths_parser.y
	bison -v -d src/maths_parser.y -o src/maths_parser.tab.cpp

src/maths_lexer.yy.cpp : src/maths_lexer.flex src/maths_parser.tab.hpp
	flex -o src/maths_lexer.yy.cpp  src/maths_lexer.flex

bin/print_mips : src/print_mips.o src/maths_parser.tab.o src/maths_lexer.yy.o src/maths_parser.tab.o bin/Context.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/print_mips $^
	
bin/print_py : src/print_py.o src/maths_parser.tab.o src/maths_lexer.yy.o src/maths_parser.tab.o bin/Context.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/print_py $^

bin/c_compiler : src/c_compiler.o src/maths_parser.tab.o src/maths_lexer.yy.o src/maths_parser.tab.o bin/Context.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/c_compiler $^
	
bin/eval_expr : src/eval_expr.o src/maths_parser.tab.o src/maths_lexer.yy.o src/maths_parser.tab.o bin/Context.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/eval_expr $^

clean :
	rm src/*.o
	rm bin/*
	rm src/*.tab.cpp
	rm src/*.yy.cpp
