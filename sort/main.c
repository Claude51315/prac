#ifdef LIST
#include "list.h"
#elif ARRAY
#include "array.h"
#endif
#include "time_measure.h"
#include<string.h>
int main(int argc, char *argv[])
{
    struct timespec start, end;
    double duration = 0;
    int n = atoi(argv[1]);
    char filename[15];
    FILE *p;
#ifdef LIST
    list_t *the_list,*sorted_list;
    the_list = init_list();
    int tmp ;
    p = fopen("random_number.txt", "r");
    while(1) {
        fscanf(p, "%d", &tmp);
        if(feof(p))
            break;
        the_list = list_insert(the_list, tmp);
    }
    fclose(p);
    clock_gettime(CLOCK_ID, &start);
#ifdef BUBBLE
    sorted_list = bubble_sort(the_list);
#elif MERGE
    sorted_list = merge_sort(the_list);
#else
    sorted_list = quick_sort(the_list, 0, the_list->length -1);
#endif
    clock_gettime(CLOCK_ID, &end);
    print("sorted_number.txt", sorted_list);
    free_list(sorted_list);
#endif

#ifdef ARRAY
    int *data;
    data = malloc(n * sizeof(int));
    int tmp , i = 0;
    p = fopen("random_number.txt", "r");
    while(1) {
        fscanf(p, "%d", &tmp);
        if(feof(p))
            break;
        data[i++] = tmp;
    }
    fclose(p);
    clock_gettime(CLOCK_ID, &start);
#ifdef BUBBLE
    bubble_sort(data, n);
#elif MERGE
    merge_sort(data, n);
#else
    quick_sort(data, 0, n-1);
#endif
    clock_gettime(CLOCK_ID, &end);
    print(data, n, "sorted_number.txt");
    free(data);
#endif
    duration = diff_in_second(start, end);
    printf("duration = %lf\n", duration);

    /* output execution time*/
#ifdef LIST
#ifdef BUBBLE
    strcpy(filename, "BUBBLE_LIST");
#elif MERGE
    strcpy(filename, "MERGE_LIST");
#else
    strcpy(filename, "QUICK_LIST");
#endif
#else
#ifdef BUBBLE
    strcpy(filename, "BUBBLE_ARRAY");
#elif MERGE
    strcpy(filename, "MERGE_ARRAY");
#else
    strcpy(filename, "QUICK_ARRAY");
#endif
#endif
    p = fopen("execution_time.txt", "a");
    fprintf(p,"%s,%d,%lf\n", filename, n, duration);
    fclose(p);
    return 0 ;
}
