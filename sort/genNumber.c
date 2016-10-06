#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#define N 20
int main(){


    int i , tmp;
    srand(time(NULL));
    FILE* p = fopen("random_number.txt", "w");
    for(i = 0 ; i < N ; i ++)
    {
        tmp = rand()%N; 
        fprintf(p, "%d\n", tmp);
    }
    fclose(p);
    return 0;
}
