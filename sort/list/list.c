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
    p->length = 0 ;
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
    node_t *elem = the_list->head;
    the_list->length ++;
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
    /*
    node_t *elem = the_list->head;
    int length = 0;
    while(elem->next != NULL)
    {
        length++;
        elem = elem->next; 
    }
    */
    return the_list->length ;
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
list_t* quick_sort(list_t *the_list, int start, int end)
{
    if(start > end)
        return the_list; 
    node_t *pivot, *left = NULL, *end_elem; 
    node_t *elem;
    int length = 0;
    pivot = list_get(the_list, start);
    end_elem = list_get(the_list, end);
    elem = pivot;
    while(elem->next != end_elem->next && elem->next != NULL)
    {
        if(elem->next->value < pivot->value){
            if(left == NULL){
                swap(the_list, pivot->next, elem->next);
                left = pivot->next;
            }else{
                swap(the_list, left->next, elem->next);
                left = left->next;
            }
            length++;
        }
        elem = elem->next;
    }
    swap(the_list, pivot, left);
    quick_sort(the_list, start, start+length-1);
    quick_sort(the_list, start+length+1, end);
    //printf("length = %d\n", length);
    return the_list;
}
list_t* merge_sort(list_t *the_list, int mode )
{
    list_t *left, *right, *merged, *left_tmp, *right_tmp; 
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
    left_tmp = merge_sort(left, mode);
    printf("left:\n");
    print(NULL, left_tmp);
    right_tmp = merge_sort(right, mode );
    printf("right:\n");
    print(NULL, right_tmp);


    if(mode == 0){
        merged = merge(left_tmp, right_tmp);
    } else if (mode == 1){
        merged = merge_inplace(left_tmp, right_tmp);
    }
    printf("merged:\n");
    print(NULL, merged);
    free_list(left_tmp);
    free_list(right_tmp);
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
        printf("test\n");
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
list_t* merge_inplace(list_t *the_list1, list_t *the_list2)
{
    list_t *new_list = init_list();
    node_t *elem1, *elem2, *elem_new;
    elem_new = new_list->head; 
    // avoid circular pointing
    elem1 = the_list1->head->next;
    elem2 = the_list2->head->next;
    while(elem1 != NULL && elem2 !=NULL)
    {
        printf("elem1 ->value = %d\n", elem1->value);
        printf("elem2 ->value = %d\n", elem2->value);
        if(elem1->value < elem2->value){
            elem_new -> next = elem1;
            elem_new = elem_new->next; 
            elem1 = elem1->next;
        }else{
            elem_new -> next = elem2;
            elem_new = elem_new->next;
            elem2 = elem2->next;
        }
    }
    if(elem1!=NULL)
    {
        elem_new->next = elem1;
    }
    if(elem2!=NULL)
    {
        elem_new->next = elem2;
    }
    new_list -> length = the_list1->length + the_list2->length;
    the_list1->head->next = NULL; 
    the_list2->head->next = NULL;
    return new_list;
}
void print(char* filename, list_t *the_list)
{
    FILE *p = NULL;
    if(filename != NULL)
        p = fopen(filename, "w");
    node_t *elem = the_list->head; 
    while(elem->next!=NULL)
    {
        if(p != NULL)
            fprintf(p,"%d\n", elem->next->value);
        else
            printf("%d\n", elem->next->value);
        elem = elem->next; 
    }
    if(filename != NULL)
        fclose(p);
}
