CC=g++ -std=c++1y -Wall
NAME=main
SRC_DIR=src
BIN_DIR=bin
OBJ_DIR=obj


$(NAME): $(NAME).o neuron.o weight.o nn.o act_func.o
	$(CC) -o $@ $^

$(NAME).o: $(NAME).cpp
	$(CC) -c $<

neuron.o: neuron.cpp neuron.h
	$(CC) -c $<

weight.o: weight.cpp weight.h
	$(CC) -c $<

nn.o: nn.cpp nn.h
	$(CC) -c $<

act_func.o: act_func.cpp act_func.h
	$(CC) -c $<


.phony: clean
clean:
	rm -f $(NAME) *.o *~
