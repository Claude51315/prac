#ifndef CUSTOM_LIST_H
#define CUSTOM_LIST_H
#include<stdio.h>
#include<stdlib.h>
/* list struct*/
typedef struct _node{
	int value;
	struct _node *next;
}node_t;
typedef struct _list{
	node_t *head;
}list_t;
/* list operation*/
node_t* new_node(int val, node_t* next);
list_t* init_list();
list_t* insert(list_t *the_list, int value);
void print(list_t *the_list);
/* list sorting */
list_t* bubble_sort(list_t *the_list);
void swap(node_t *a, node_t *b);
#endif