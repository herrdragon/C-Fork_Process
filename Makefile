FILES = *.c
CC = gcc

BUILD: $(FILES)
	$(CC) $(FILES) -o fork.out
