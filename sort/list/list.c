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
void free_list(list_t *the_list)
{
    node_t *elem, *tmp;
    elem = the_list->head;
    while(elem->next!=NULL)
    {
        tmp = elem ; 
        elem = elem->next;
        tmp->next = NULL ; 
        free(tmp);
    }
    free(the_list);
}
list_t* list_insert(list_t *the_list, int value)
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
int list_length(list_t *the_list)
{
    node_t *elem = the_list->head;
    int length = 0;
    while(elem->next != NULL)
    {
        length++;
        elem = elem->next; 
    }
    return length;
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
list_t* quick_sort(list_t *the_list)
{
    return the_list;
}
list_t* merge_sort(list_t *the_list)
{
    list_t *left, *right, *merged; 
    node_t *elem;
    int length, i; 
    length = list_length(the_list);
    if(length < 2)
        return the_list;
    
    left = init_list();
    right = init_list();
    elem = the_list->head;
    for(i = 0; i < length; i++)
    {
        elem = elem->next; 
        if(i < length/2){
            list_insert(left, elem->value);
        }else{
            list_insert(right, elem->value);
        }
    }
    left = merge_sort(left);
    right = merge_sort(right);
    merged = merge(left, right);
    free_list(left);
    free_list(right);
    return merged;
}
list_t* merge(list_t *the_list1, list_t *the_list2)
{
    
    list_t *new_list = init_list();
    node_t *elem1, *elem2;
    elem1 = the_list1->head;
    elem2 = the_list2->head;
    while(elem1->next != NULL && elem2->next !=NULL)
    {
        if(elem1->next->value < elem2->next->value){
            list_insert(new_list, elem1->next->value);
            elem1 = elem1->next;
        }else{
            list_insert(new_list, elem2->next->value);
            elem2 = elem2->next;
        }
    }
    while(elem1->next!=NULL)
    {
        list_insert(new_list, elem1->next->value);
        elem1 = elem1->next;
    }
    while(elem2->next!=NULL)
    {
        list_insert(new_list, elem2->next->value);
        elem2 = elem2->next;
    }
    return new_list;
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
