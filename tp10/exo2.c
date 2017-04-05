#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 4 


void remplirTableau(int T[N]){
	int i, val;
	for(i = 0; i < N; i++){
		val = -1;
		while (val < 0 || val >=100){
			printf("Entrez la valeur %d du tableau (entier positif inferieur a 100)\n",i);
			scanf("%d", &val);
			if(val < 0 || val >=100){
				printf("Valeur incorrecte ! \n");
			}
		}
		T[i] = val;
	}	
}

void afficherTableau(int T[N]){
	int i;
	for(i = 0; i < N; i++){
		printf("%d\t", T[i]);
	}
	printf("\n");
}

void copierTab(int T1[N], int T2[N]) {
    int i;
    for (i = 0; i < N; i++) {
        T2[i] = T1[i];
    }
}

void triBulle(int T1[N], int T2[N], char compare(int a, int b)){
	int i, j, tmp;
	copierTab(T1,T2);
	for(i = N - 1; i > 0; i--){
		for(j = 0; j < i; j++){
			if (compare(T2[j+1],T2[j])==1){
				tmp = T2[j+1];
				T2[j+1] = T2[j];
				T2[j] = tmp;
			}
		}
	}
}

int sup(const void* A, const void* B){
    int a = *(int*) A;
    int b = *(int*) B;
    return (a>b)?1:((a<b)?-1:0);
}

int inf(const void* A, const void* B){
    int a = *(int*) A;
    int b = *(int*) B;
    return (a<b)?1:((a>b)?-1:0);
}

int main(){
    int t[N];
    int t2[N];
    remplirTableau(t);
    afficherTableau(t);
    qsort(t,N,sizeof(int),inf);
    afficherTableau(t);
    return 0;
}
