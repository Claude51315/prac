#include "list.h"
node_t* new_node(int val, node_t* next)
{
	node_t *p = (node_t*)malloc(sizeof(node_t));
	if(p == NULL){
		printf("memory allocation error\n");
		exit(1);
	}
	p->value = val ; 
	p->next = next;
	return p; 
}
list_t* init_list()
{
	list_t *p =(list_t*) malloc(sizeof(list_t));
	if(p == NULL){
		printf("memory allocation error\n");
		exit(1);
	}
	p->head = new_node(0, NULL); 
	return p; 
}
list_t* insert(list_t *the_list, int value)
{
	node_t *elem = the_list->head ; 
	node_t *prev; 
	if(elem->next == NULL)
	{
		elem->next = new_node(value, NULL); 
		return the_list; 
	}
	prev = elem ; 
	while( elem->next != NULL)
	{
		prev = elem ; 
		elem = elem->next ; 
	}
	elem->next = new_node(value, NULL); 

	return the_list; 
}
list_t* bubble_sort(list_t *the_list)
{
	node_t *next;
	node_t *elem;
	elem = the_list->head ; 
	while(elem->next != NULL)
	{
		elem = elem->next; 
		next = elem; 
		while(next != NULL){
			if(next->value < elem->value)
				swap(next, elem);
			next = next->next; 
		}
	}
	return the_list; 
}
void swap(node_t *a, node_t *b)
{
	/* swap the value of the two nodes*/
	int tmp = a->value; 
	a->value = b->value; 
	b->value = tmp ; 
}
void print(list_t *the_list)
{
	node_t *elem = the_list->head; 
	while(elem->next!=NULL)
	{
		printf("%d\n", elem->next->value);
		elem = elem->next; 
	}
}