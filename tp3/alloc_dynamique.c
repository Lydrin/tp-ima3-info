#include<stdio.h>
#include<stdlib.h>

#define SIZE 4000


int main(void)
{
    int* v = (int*)malloc(SIZE * sizeof(int));
    int** mat = (int**)malloc(SIZE *sizeof(int *));
    int i;
    for(i=0;i<SIZE;i++)
    {
        *(mat + i)=(int*)malloc(SIZE * sizeof(int));
    }
    return 0;
}
