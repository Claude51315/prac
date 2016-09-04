#include "list.h"
#define N 100
int main(void)
{
    list_t *the_list;
    the_list = init_list();
    int i ;
    for(i = 0; i < N ; i ++)
        insert(the_list, N-i);
    print(the_list);
    the_list = bubble_sort(the_list);
    print(the_list);
    printf("\n");
    return 0 ;
}
