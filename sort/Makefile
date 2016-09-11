CC=gcc
CFLAG += -std=c99
CFLAG += -Wall
CFLAG += -g
all: merge_sort bubble_sort quick_sort perf

bubble_sort: list/bubble_sort.c list/list.h list/list.c
	$(CC) $(CFLAG) list/bubble_sort.c list/list.h list/list.c -o bubble_sort

merge_sort: list/merge_sort.c list/list.h list/list.c
	$(CC) $(CFLAG) list/bubble_sort.c list/list.h list/list.c -o merge_sort

quick_sort: list/quick_sort.c list/list.h list/list.c
	$(CC) $(CFLAG) list/quick_sort.c list/list.h list/list.c -o quick_sort



perf:
	sudo perf stat --repeat 10 -e cycles ./bubble_sort
	sudo perf stat --repeat 10 -e cycles ./merge_sort
	sudo perf stat --repeat 10 -e cycles ./quick_sort

.PHONY: clean run

clean:
	-rm bubble_sort
	-rm merge_sort
	-rm quick_sort
