#include<time.h>
#include<stdlib.h>
#include<stdio.h>
int main(int argc, char *argv[])
{

    int N  = atoi(argv[1]);
    int i , tmp;
    srand(time(NULL));
    FILE* p = fopen("random_number.txt", "w");
    for(i = 0 ; i < N ; i ++) {
        tmp = rand()%N;
        fprintf(p, "%d\n", tmp);
    }
    fclose(p);
    return 0;
}
