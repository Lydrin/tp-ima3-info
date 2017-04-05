#include <stdio.h>
#include <stdlib.h>

#define N 10


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

void triBulle(int T1[N], int T2[N]){
	int i, j, tmp;
	copierTab(T1,T2);
	for(i = N - 1; i > 0; i--){
		for(j = 0; j < i; j++){
			if (T2[j+1] < T2[j]){
				tmp = T2[j+1];
				T2[j+1] = T2[j];
				T2[j] = tmp;
			}
		}
	}
}

int main(){
	printf("EXAM TP 03/01/2017\nDelobelle Matthieu - TD1\n");
	int i;
	int cpt = 0;
	int T1[N];
	int T2[N];
	remplirTableau(T1);
	afficherTableau(T1);
	triBulle(T1,T2);
	afficherTableau(T2);
}