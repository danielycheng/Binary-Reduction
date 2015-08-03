# Daniel Cheng - dyc8av
# Written February 18, 2015
# makefile for HW2, includes barrier.h barrier.cpp main.cpp

all: main.cpp barrier.cpp 
	g++ main.cpp barrier.cpp -lpthread -o max

clean:
	-rm -f *.o *~
