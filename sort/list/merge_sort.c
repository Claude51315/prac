#include "list.h"
#define N 100
#include "time_measure.h"
int main(void)
{
    struct timespec start, end; 

    list_t *the_list,*merge_list;
    the_list = init_list();
    int i ;
    double duration; 
    for(i = 0; i < N; i++)
    {
        list_insert(the_list, N - i);
    }
    clock_gettime(CLOCK_ID, &start);
    merge_list = merge_sort(the_list, 1 );
    clock_gettime(CLOCK_ID, &end);
    duration = diff_in_second(start, end);
    printf("duration = %lf", duration);
    print(merge_list);
    
    return 0 ;
}
