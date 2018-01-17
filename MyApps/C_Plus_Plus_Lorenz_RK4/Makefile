CC = g++
FLAGS = -std=c++1y -Wall
LIBS = -lGL -lGLU -lglut

all: main

main: main.o rk4.o
	$(CC) $(FLAGS) -o $@ $^ $(LIBS)

main.o: main.cpp
	$(CC) $(FLAGS) -c $<

rk4.o: rk4.h rk4.cpp
	$(CC) $(FLAGS) -c $^

.phony: clean
clean:
	rm -f *~ *.o main *.gch
