#include<stdio.h>

#define SIZE 400

int main(void)
{
    int M[SIZE][SIZE],i,j;
    for(i=0;i<SIZE;i++)
    {
        for(j=0;j<SIZE;j++)
        {
            M[i][j]=i+j;
        }
    } 
    return 0;
}
