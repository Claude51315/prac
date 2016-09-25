#include "list.h"
#define N 1000
int main(void)
{
    struct timeval start, end;
    long int duration;
    list_t *the_list;
    the_list = init_list();
    int i ;
    for(i = 0; i < N; i++)
    {
        list_insert(the_list, N-i);
    }
    gettimeofday(&start, NULL);
    quick_sort(the_list, 0, the_list->length-1);
    gettimeofday(&end, NULL);
    duration = end.tv_sec *1000 + end.tv_usec / 1000 ; 
    duration = duration - start.tv_sec *1000 - start.tv_usec / 1000;
    printf("duration = %ld\n", duration);
    return 0 ;
}
