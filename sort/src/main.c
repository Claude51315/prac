#include "list.h"
#define N 100
int main(void)
{
    list_t *the_list;
    the_list = init_list();
    int i ;
    for(i = 0 ; i < N ; i ++)
        insert(the_list, i);
    print(the_list);
    return 0 ;
}
