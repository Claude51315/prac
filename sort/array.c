#include "array.h"
void merge_sort(int *data, int n)
{
    if(n < 2)return ;
    int mid, i, *L, *R;
    mid  = n / 2;
    L =(int*) malloc(sizeof(int) * mid);
    R =(int*) malloc(sizeof(int) * (n - mid));
    for(i = 0; i < mid; i++)
        L[i] = data[i];
    for(i = mid ; i < n; i++)
        R[i-mid] = data[i] ;
    merge_sort(L, mid);
    merge_sort(R, n-mid);
    merge(data, L, mid, R, n-mid);
    free(L);
    free(R);
}

void merge(int *data, int *L, int l_len, int *R, int r_len)
{
    int i, j, k;
    /*
    	i : left array index
    	j : right array index
    	k : merge array index
    */
    i = 0 ;
    j = 0 ;
    k = 0;

    while(i < l_len && j < r_len) {
        if(L[i] < R[j]) data[k++] = L[i++];
        else data[k++] = R[j++];
    }
    while(i < l_len) data[k++] = L[i++];
    while(j < r_len) data[k++] = R[j++];
    return ;
}
void quick_sort(int *data, int start, int end)
{
    if(start > end) return;
    int pivot = data[start];
    int l, r, tmp;
    /* partition */
    l = start;
    r = end;
    while(l < r) {
        while(l < end && data[l] <= pivot) l++;
        while(r > start && data[r] > pivot) r--;
        if(l < r) {
            tmp = data[l];
            data[l] = data[r];
            data[r] = tmp;
        }
    }
    data[start] = data[r];
    data[r] = pivot;
    /*divide and conquer*/
    quick_sort(data, start, r-1);
    quick_sort(data, r+1, end);
}
void bubble_sort(int *data, int n)
{
    int i, j;
    for(i = 0 ; i < n ; i++)
        for(j = i+1 ; j < n ; j++) {
            if(data[j] < data[i]) {
                data[j] = data[j] ^ data[i];
                data[i] = data[j] ^ data[i];
                data[j] = data[j] ^ data[i];
            }
        }
}
void print(int *data, int n, char* filename)
{
    FILE *p = NULL;
    if(filename != NULL)
        p = fopen(filename, "w");
    for(int i = 0; i < n; i++) {
        if(p == NULL)
            printf("%d\n", data[i] );
        else
            fprintf(p, "%d\n", data[i] );
    }
    if(p!=NULL)
        fclose(p);
}
