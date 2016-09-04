CC=gcc
CFLAG += -std=c99
CFLAG += -Wall
CFLAG += -g
all: mergeS bubbleS

bubbleS: list/bubble_sort.c list/list.h list/list.c
	$(CC) $(CFLAG) list/bubble_sort.c list/list.h list/list.c -o bubble_sort

mergeS: list/merge_sort.c list/list.h list/list.c
	$(CC) $(CFLAG) list/bubble_sort.c list/list.h list/list.c -o merge_sort


perf:
	sudo perf stat --repeat 10 -e cycles ./bubble_sort
	sudo perf stat --repeat 10 -e cycles ./merge_sort

.PHONY: clean run

clean:
	-rm bubble_sort
	-rm merge_sort
