CC = g++
FLAGS = -std=c++1y -Wall
LIBS = -lGL -lGLU -lglut

all: main

main: welzl.o
	$(CC) $(FLAGS) -o $@ $^ $(LIBS)

rk4.o: welzl.cpp
	$(CC) $(FLAGS) -c $^

.phony: clean
clean:
	rm -f *~ *.o main *.gch
