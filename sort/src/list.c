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
    node_t *prev;
    node_t *elem = the_list->head ; 
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
node_t* list_get(list_t *the_list, int index)
{
    if(index < 0)
        return NULL;
    node_t *elem = the_list->head; 
    int i ; 
    for(i = 0; i < index+1; i++)
    {
        elem = elem->next ; 
        if(elem == NULL)
            return NULL;
    }
    return elem; 
}
list_t* bubble_sort(list_t *the_list)
{
	node_t *next;
	node_t *elem;
	elem = the_list->head ; 
	while(elem->next != NULL)
	{
        next = elem->next; 
        while(next->next!=NULL)
        {
            if(elem->next->value > next->next->value)
                swap(the_list, elem->next, next->next);
            next = next->next; 
            if(next == NULL)
                break; 
        }
	    elem = elem->next;
    }
	return the_list; 
}
void swap(list_t *the_list, node_t *a, node_t *b)
{
    if( a == b)
        return ; 
    node_t *a_prev=NULL, *b_prev=NULL; 
    node_t *elem = the_list->head; 
    while(elem->next != NULL)
    {
        if(elem->next == a )
            a_prev = elem;
        if(elem->next == b)
            b_prev = elem;
        elem = elem->next; 
    }
    /* a or b is not in the list */
    if(a_prev == NULL || b_prev == NULL)
        return; 
    /* consider whether a and b are adjacent*/ 
    if(a_prev != b)
        a_prev->next = b ;
    if(b_prev != a)
        b_prev->next = a ;
    elem = a->next;
    if(b->next != a)
        a->next = b->next;
    else
        a->next = b; 
    if(elem != b)
        b->next = elem;
    else
        b->next = a ; 
}
void print(list_t *the_list)
{
	node_t *elem = the_list->head; 
	while(elem->next!=NULL)
	{
		printf("%d ", elem->next->value);
		elem = elem->next; 
	}
    printf("\n");
}
