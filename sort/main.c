#ifdef LIST
#include "list.h"
#elif ARRAY
#include "array.h"
#endif
#include "time_measure.h"
int main(void)
{
    struct timespec start, end;
    double duration = 0;
#ifdef LIST
    list_t *the_list,*sorted_list;
    the_list = init_list();
    int tmp ;
    FILE *p = fopen("random_number.txt", "r");
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
    int n = 50;
    data = malloc(n * sizeof(int));

    int tmp , i = 0;
    FILE *p = fopen("random_number.txt", "r");
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
    return 0 ;
}
