CXX	= g++

.cc.o:
	$(CXX) -c $< -o $*.o

default: all

all: tubecode TubeIC

TubeIC.tab.cc: TubeIC.y
	bison -oTubeIC.tab.cc -b TubeIC -d TubeIC.y

TubeIC.yy.cc: TubeIC.lex
	flex -oTubeIC.yy.cc TubeIC.lex

TubeIC: TubeIC.tab.o TubeIC.yy.o inst.o hardware.o
	$(CXX) -o TubeIC TubeIC.tab.o TubeIC.yy.o inst.o hardware.o -ll -ly

tubecode.tab.cc: tubecode.y
	bison -otubecode.tab.cc -b tubecode -d tubecode.y

tubecode.yy.cc: tubecode.lex
	flex -otubecode.yy.cc tubecode.lex

tubecode: tubecode.tab.o tubecode.yy.o inst.o hardware.o
	$(CXX) -o tubecode tubecode.tab.o tubecode.yy.o inst.o hardware.o -ll -ly

clean:
	rm -f TubeIC.tab.cc TubeIC.tab.hh TubeIC.yy.cc TubeIC tubecode.tab.cc tubecode.tab.hh tubecode.yy.cc tubecode *~ *.o
