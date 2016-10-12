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
    p->head = new_node(0, NULL);;
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
    e->next = the_list->head->next;
    the_list->head->next = e;
    //the_list->head = e;
    return the_list;
}
node_t* list_index(list_t *the_list, int index)
{
    if(index < 0 || index >= the_list->length)
        return NULL;
    node_t *elem = the_list->head;
    int i ;
    for(i = 0; i <= index; i++) {
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
    node_t *next;
    node_t *elem;
    elem = the_list->head ;
    while(elem->next != NULL) {
        next = elem->next;
        while(next && next->next ) {
            if(elem->next->value > next->next->value) {
                swap(the_list, elem->next, next->next);
            }
            next = next->next;
        }
        elem = elem->next;
    }
    return the_list;
}
void swap(list_t *the_list, node_t *a, node_t *b)
{
    if( a == b || a== NULL || b == NULL)
        return ;

    int tmp;
    tmp = a->value;
    a->value = b->value;
    b->value = tmp;
    return;


    node_t *a_prev=NULL, *b_prev=NULL;
    node_t *elem = the_list->head;
    int count = 0;
    while(elem->next != NULL) {
        if(elem->next == a ) {
            a_prev = elem;
        }
        if(elem->next == b) {
            b_prev = elem;
        }
        elem = elem->next;
    }

    /*   a or b is not in the list*/
    if( a_prev == NULL || b_prev == NULL )
        return;

    elem = a_prev->next;
    a_prev->next = b_prev->next;
    b_prev->next = elem;

    elem = a ->next ;
    a->next = b->next;
    b->next = elem;

    /* consider whether a and b are adjacent*/
    if(a_prev != b) {
        a_prev->next = b ;
    }
    if(b_prev != a) {
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
    /*
    printf("start\n");
    print(NULL, the_list);
    printf("start = %d\n", start);
    printf("end = %d\n", end);
    printf("-----\n");
    */
    if(start >= end)
        return the_list;
    node_t *pivot, *left = NULL;
    node_t *elem, *end_elem, *tmp;
    int length = 0;
    pivot = list_index(the_list, start);
    end_elem = list_index(the_list, end);
    elem = pivot->next;
    while(elem != end_elem->next && elem != NULL) {
        if(elem->value <= pivot->value) {
            if(left == NULL) {
                left = elem;
                elem = elem->next;
                swap(the_list, pivot->next, left);
            } else {
                tmp = elem;
                elem = elem->next;
                swap(the_list, left->next, tmp);
                left = left->next;
            }
            length++;
        } else {
            elem = elem->next;
        }
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
    while(elem->next!=NULL) {
        if(p != NULL)
            fprintf(p,"%d\n", elem->next->value);
        else
            printf("%d\n", elem->next->value);
        elem = elem->next;
    }
    if(filename != NULL)
        fclose(p);
}
