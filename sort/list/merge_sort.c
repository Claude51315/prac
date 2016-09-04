#include "list.h"
#define N 1000
int main(void)
{
    list_t *the_list,*merge_list;
    the_list = init_list();
    int i ;
    for(i = 0; i < N; i++)
    {
        list_insert(the_list, N - i);
    }
    merge_list = merge_sort(the_list);
    return 0 ;
}
