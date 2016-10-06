#ifndef CUSTOM_LIST_H
#define CUSTOM_LIST_H
#include<stdio.h>
#include<stdlib.h>
/* list struct*/
typedef struct _node {
    int value;
    struct _node *next;
} node_t;
typedef struct _list {
    node_t *head;
    int length;
} list_t;
/* list operation*/
node_t* new_node(int val, node_t* next);
list_t* init_list();
void free_list(list_t *the_list);
list_t* list_insert(list_t *the_list, int value);
node_t* list_get(list_t *the_list, int index);
void swap(list_t *the_list, node_t *a, node_t *b);
int list_length(list_t *the_list);
void print(char* filename, list_t *the_list);
/* list sorting */
list_t* bubble_sort(list_t *the_list);
list_t* quick_sort(list_t *the_list, int start, int end);

list_t* merge_sort(list_t *the_list, int mode);
list_t* merge(list_t *the_list1, list_t *the_list2);
list_t* merge_inplace(list_t *the_list1, list_t* the_list2);
#endif
