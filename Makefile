CC = gcc

SRC = main.c object.c mark-and-sweep.c
OBJ = main.o object.o mark-and-sweep.o
EXEC = main

all: $(EXEC)
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) -c $< -o $@

clean: 
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean