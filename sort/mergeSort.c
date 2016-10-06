#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 100

void merge_sort(int *data, int n);
void merge(int *result, int *L, int l_len, int *R, int r_len);
void print(int *data, int n);
int main()
{

    int data[N];
    srand(time(NULL));
    for(int i = 0 ; i < N; i++)
        data[i] = rand()%(N*10);
    print(data ,N);
    merge_sort(data, N);
    print(data ,N);
    return 0 ;
}
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
void print(int *data, int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", data[i] );
    printf("\n");
}
