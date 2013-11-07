CXX	= g++

.cc.o:
	$(CXX) -Wno-write-strings -c $< -o $*.o

default: all

all: tube-ic

fais.tab.cc: fais.y ast.h
	bison -ofais.tab.cc -b fais -d fais.y

fais.yy.cc: fais.lex ast.h
	flex -ofais.yy.cc fais.lex

tube-ic: fais.tab.o fais.yy.o ast.h
	$(CXX) -o tube-ic fais.tab.o fais.yy.o -ll -ly

clean:
	rm -f fais.tab.cc fais.tab.hh fais.yy.cc fais.tab.o fais.yy.o tube-ic
