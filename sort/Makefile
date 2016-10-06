CC=gcc
CFLAG += -std=gnu99
CFLAG += -Wall
CFLAG += -g
all: merge_sort bubble_sort quick_sort

bubble_sort: list/bubble_sort.c list/list.h list/list.c
	$(CC) $(CFLAG) list/bubble_sort.c list/list.h list/list.c -o bubble_sort

merge_sort: main.c list/list.h list/list.c 
	$(CC) $(CFLAG) main.c -I list/ list/list.c list/time_measure.c -o merge_sort

quick_sort: list/quick_sort.c list/list.h list/list.c
	$(CC) $(CFLAG) list/quick_sort.c list/list.h list/list.c -o quick_sort

genNumber: genNumber.c
	${CC} ${CFLAG} $@.c -o $@

perf:
	sudo perf stat --repeat 10 -e cycles ./bubble_sort
	sudo perf stat --repeat 10 -e cycles ./merge_sort
	sudo perf stat --repeat 10 -e cycles ./quick_sort

.PHONY: clean run test astyle

astyle:
	astyle --style=kr --indent=spaces=4 --indent-switches --suffix=none *.c *.h
test: genNumber merge_sort
	./genNumber
	./merge_sort

clean:
	-rm bubble_sort
	-rm merge_sort
	-rm quick_sort
	-rm genNumber *.txt
