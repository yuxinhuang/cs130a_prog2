#Makefile
CXX=g++
CXXFLAGS = -Wall -Wextra -Werror
BINARIES=prog2
all: ${BINARIES}



prog2: splaytree.o main.o
	${CXX} -std=c++11 $^ -o  $@ 

clean:
	/bin/rm -f ${BINARIES} *.o