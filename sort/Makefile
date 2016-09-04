CC=gcc
CFLAG += -std=c99
CFLAG += -Wall
CFLAG += -g
all: main

main: src/main.c src/list.h src/list.c
	$(CC) $(CFLAG) src/main.c src/list.h src/list.c -o main


.PHONY: clean run

clean:
	-rm main
	-rm output.txt
run:
	./main > output.txt
