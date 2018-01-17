CC = g++
FLAGS = -std=c++1y -Wall

all: main

main: julia.cpp
	$(CC) $(FLAGS) -o $@ $^


.phony: clean

clean:
	rm -f *~ *.o main
