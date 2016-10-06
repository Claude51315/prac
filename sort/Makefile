CC=gcc
CFLAG += -std=gnu99
CFLAG += -Wall
CFLAG += -g

EXECUTABLES= bubble_sort_array\
			 bubble_sort_list \
			 merge_sort_array \
			 merge_sort_list \
			 quick_sort_array \
			 quick_sort_list \
			 genNumber

COMMON= main.c time_measure.h time_measure.c
LIST_COMMON= list.h list.c
ARRAY_COMMON= array.h array.c

all: ${EXECUTABLES}

bubble_sort_array: ${COMMON} ${ARRAY_COMMON}
	$(CC) $(CFLAG) -DARRAY -DBUBBLE array.c time_measure.c main.c -o $@
bubble_sort_list: ${COMMON} ${LIST_COMMOM}
	$(CC) $(CFLAG) -DLIST -DBUBBLE list.c time_measure.c main.c -o $@

merge_sort_array: ${COMMON} ${ARRAY_COMMON}
	$(CC) $(CFLAG) -DARRAY -DMERGE array.c time_measure.c main.c -o $@
merge_sort_list: ${COMMON} ${LIST_COMMON}
	$(CC) $(CFLAG) -DLIST -DMERGE list.c time_measure.c main.c -o $@

quick_sort_array: ${COMMON} ${ARRAY_COMMON}
	$(CC) $(CFLAG) -DARRAY -DQUICK array.c time_measure.c main.c -o $@
quick_sort_list: ${COMMON} ${LIST_COMMON}
	$(CC) $(CFLAG) -DLIST -DQUICK list.c time_measure.c main.c -o $@
genNumber: genNumber.c
	${CC} ${CFLAG} $@.c -o $@
	./$@

.PHONY: clean run test astyle

astyle:
	astyle --style=kr --indent=spaces=4 --indent-switches --suffix=none *.c *.h
test: genNumber merge_sort
	./genNumber
	./merge_sort

clean:
	-rm ${EXECUTABLES} *.txt
