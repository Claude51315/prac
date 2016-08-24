#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 100

void quick_sort(int *data, int start, int end);
void print(int *a, int n);
int main(){
	int a[N]; 
	srand(time(NULL));
	for(int i = 0 ; i < N; i++)
		a[i] = rand()%(N*10);
	print(a ,N);
	quick_sort(a , 0 , N-1); 
	print(a ,N);
	return 0 ; 
}
void quick_sort(int *data, int start , int end )
{
	if(start >= end ) return ;
	int pivot = data[start]; 
	int l , r, tmp;
	// partition
	l = start ; 
	r = end; 
	while(l < r)
	{
		while(l < end && data[l] <= pivot) l++; 
		while(r > start && data[r] > pivot) r--; 
		if(l <  r){ 
		// swap 
		tmp = data[l];
		data[l] = data[r] ; 
		data[r] = tmp;
		}
	}
	data[start] = data[r] ; 
	data[r] = pivot ;

	quick_sort(data , start , r-1 ) ; 
	quick_sort(data , r+1 , end);
}
void print(int *a, int n)
{
	for(int i = 0 ; i < n ;i++)
		printf("%d ", a[i] );
	printf("\n" );
}
