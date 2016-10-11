#include "list.h"
node_t* new_node(int val, node_t* next)
{
    node_t *p = malloc(sizeof(node_t));
    if(p == NULL) {
        printf("memory allocation error\n");
        exit(1);
    }
    p->value = val ;
    p->next = next;
    return p;
}
list_t* init_list()
{
    list_t *p =malloc(sizeof(list_t));

    if(p == NULL) {
        printf("memory allocation error\n");
        exit(1);
    }
    p->head = NULL;
    p->length = 0 ;
    return p;
}
void free_list(list_t *the_list)
{
    node_t *elem, *tmp;
    elem = the_list->head;
    while(elem!=NULL) {
        tmp = elem ;
        elem = elem->next;
        tmp->next = NULL ;
        free(tmp);
    }
    free(the_list);
}
list_t* list_insert(list_t *the_list, int value)
{
    node_t *e = new_node(value, NULL);
    the_list->length ++;
    e->next = the_list->head;
    the_list->head = e;
    return the_list;
}
node_t* list_index(list_t *the_list, int index)
{
    if(index < 0 || index >= the_list->length)
        return NULL;
    node_t *elem = the_list->head;
    int i ;
    for(i = 0; i < index; i++) {
        elem = elem->next ;
        if(elem == NULL)
            return NULL;
    }
    return elem;
}
int list_length(list_t *the_list)
{
    return the_list->length ;
}
list_t* bubble_sort(list_t *the_list)
{
    node_t *next, *tmp;
    node_t *elem;
    elem = the_list->head ;
    while(elem!= NULL) {
        next = elem->next;
        while(next!=NULL) {
            if(elem->value > next->value) {
                swap(the_list, elem, next);
                tmp = elem;
                elem = next;
                next = tmp;
            }
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
    node_t *a_prev=NULL, *b_prev=NULL, *elem_prev = NULL;
    node_t *elem = the_list->head;
    int count = 0;
    while(elem != NULL) {
        if(elem == a ) {
            a_prev = elem_prev;
            count ++;
        }
        if(elem == b) {
            b_prev = elem_prev;
            count ++;
        }
        elem_prev = elem;
        elem = elem->next;
    }
    /* a or b is not in the list */
    if(count < 2 )
        return;
    /* consider whether a and b are adjacent*/
    if(a_prev != b) {
        if(a_prev == NULL)
            the_list->head = b;
        else
            a_prev->next = b ;
    }
    if(b_prev != a) {
        if(b_prev == NULL)
            the_list->head = a;
        else
            b_prev->next = a ;
    }
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
    node_t *pivot, *left = NULL;
    node_t *elem;
    int length = 0;
    pivot = list_index(the_list, start);
    elem = pivot;
    while(elem->next != NULL) {
        if(elem->next->value < pivot->value) {
            if(left == NULL) {
                swap(the_list, pivot->next, elem->next);
                left = pivot->next;
            } else {
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
    return the_list;
}
list_t* merge_sort(list_t *the_list )
{
    if(the_list->length < 2)
        return the_list;
    list_t *left, *right;
    node_t *elem;
    int mid = the_list->length/2;
    left = the_list;
    right = init_list();
    elem = list_index(the_list, mid-1);
    right->head = elem->next;
    elem->next = NULL;
    right->length = the_list->length - mid;
    left->length = mid;
    return  merge_list(merge_sort(left) , merge_sort(right));
}
list_t* merge_list(list_t *a, list_t *b)
{
    list_t *new_list = init_list();
    list_t *small;
    node_t *current = NULL;
    while( a->length && b->length) {
        small = (a->head->value < b->head->value) ? a : b;
        if(current) {
            current -> next = small->head;
            current = current->next;
        } else {
            new_list->head = small->head;
            current = new_list->head;
        }
        small->head = small->head->next;
        small->length--;
        new_list->length++;
        current->next = NULL;
    }
    list_t *remaining = (a->length > 0) ? a : b ;
    if(current)
        current->next = remaining->head;
    new_list->length += remaining->length;
    a->head = NULL;
    b->head = NULL;

    free(a);
    free(b);
    return new_list;
}
void print(char* filename, list_t *the_list)
{
    FILE *p = NULL;
    if(filename != NULL)
        p = fopen(filename, "w");
    node_t *elem = the_list->head;
    while(elem!=NULL) {
        if(p != NULL)
            fprintf(p,"%d\n", elem->value);
        else
            printf("%d\n", elem->value);
        elem = elem->next;
    }
    if(filename != NULL)
        fclose(p);
}
