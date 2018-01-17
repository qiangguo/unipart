CC = mpic++

all: main

main: integral.cpp
	$(CC) -o $@ $^
	echo "mpirun -np 4 main" > run.sh
	chmod +x run.sh

.phony: clean
clean:
	rm -f *~ *.o main *.sh
