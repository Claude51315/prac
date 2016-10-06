#include "list.h"
#include "time_measure.h"
int main(void)
{
    struct timespec start, end;

    list_t *the_list,*merge_list;
    the_list = init_list();
    int i, tmp ;
    double duration;
    FILE *p = fopen("random_number.txt", "r");
    while(1) {
        fscanf(p, "%d", &tmp);
        if(feof(p))
            break;
        list_insert(the_list, tmp);
    }
    fclose(p);
    printf("complete read file\n");
    print("test.txt", the_list);
    clock_gettime(CLOCK_ID, &start);
    merge_list = merge_sort(the_list, 1);
    clock_gettime(CLOCK_ID, &end);
    duration = diff_in_second(start, end);
    printf("duration = %lf\n", duration);
    print("sorted_number.txt", merge_list);

    return 0 ;
}
