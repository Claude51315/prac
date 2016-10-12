#include<stdio.h>
#include "list.h"
int main()
{
    list_t *a = init_list();
    list_insert(a ,1);
    list_insert(a ,2);
    list_insert(a ,3);
    list_insert(a ,4);
    list_insert(a ,5);
    print(NULL, a);
    free_list(a);
    return 0;
}
