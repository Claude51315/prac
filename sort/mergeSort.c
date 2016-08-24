#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 100

void merge_sort(int *a, int n);
void merge(int *result, int *L, int l_len, int *R, int r_len);
void print(int *a, int n);
int main(){
	
	int a[N]; 
	srand(time(NULL));
	for(int i = 0 ; i < N; i++)
		a[i] = rand()%(N*10);
	print(a ,N);
	merge_sort(a, N); 
	print(a ,N);
	return 0 ; 
}
void merge_sort(int *a, int n)
{
	if(n < 2)return ; 
	int mid, i, *L, *R; 
	mid  = n /2 ; 
	L =(int*) malloc(sizeof(int) *mid);
	R =(int*) malloc(sizeof(int) *(n - mid));
	for(i = 0; i < mid ; i ++)
		L[i] = a[i]; 
	for(i = mid ; i < n ; i ++)
		R[i-mid] = a[i] ; 
	merge_sort(L , mid); 
	merge_sort(R , n-mid);
	merge(a , L , mid, R , n-mid);
	free(L);
	free(R); 
}
void merge(int *result, int *L, int l_len, int *R, int r_len)
{
	int i, j , k; 
	/*
		i : left array index 
		j : right array index 
		k :  merge array index 
	*/
	i = 0 ; j = 0 ; k = 0; 
	
	while(i < l_len && j < r_len)
	{
		if(L[i] < R[j]) result[k++] = L[i++];
		else result[k++] = R[j++];
	}
	while(i < l_len) result[k++] = L[i++]; 
	while(j < r_len) result[k++] = R[j++]; 
	return ; 
}
void print(int *a, int n)
{
	for(int i = 0 ; i < n ;i++)
		printf("%d ", a[i] );
	printf("\n" );
}