#include "list.h"
#define N 10
int main(void)
{
    list_t *the_list, *the_list2, *merge_list;
    the_list = init_list();
    the_list2 = init_list();   
    int i ;
    for(i = 0; i < N; i++)
    {
        list_insert(the_list, N - i);
        list_insert(the_list2, N - i);
    }
    merge_list = merge_sort(the_list);
    bubble_sort(the_list2);
    printf("merge sort:\n");
    print(merge_list);
    printf("bubble sort:\n");
    print(the_list2);
    return 0 ;
}
