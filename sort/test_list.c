#include<stdio.h>
#include "list.h"
int main()
{
    list_t *a = init_list(), *b;
    node_t *tmpA, *tmpB;
    list_insert(a ,1);
    list_insert(a ,23);
    list_insert(a ,666);
    list_insert(a ,44);
    list_insert(a ,5);
    print(NULL, a);
    /*
    tmpA = list_index(a, 4);
    tmpB = list_index(a, 0);
    swap(a, tmpA, tmpB);
    */
    b= bubble_sort(a);
    printf("----\n");
    print(NULL, b);
    //free_list(a);
    return 0;
}
