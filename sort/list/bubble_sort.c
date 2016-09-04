#include "list.h"
#define N 1000
int main(void)
{
    list_t *the_list;
    the_list = init_list();
    int i ;
    for(i = 0; i < N; i++)
    {
        list_insert(the_list, N - i);
    }
    bubble_sort(the_list);
    return 0 ;
}
