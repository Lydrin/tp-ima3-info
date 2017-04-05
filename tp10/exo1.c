#include<stdio.h>


int fois_deux(int a){
    return 2*a;
}

void appliquer_tableau(int f(int), int t[], int size){
    int i = 0;
    for(i=0;i<size;i++){
        t[i] = f(i);
    }
}

void affiche_tab(int t[], int size){
    int i = 0;
    for(i=0;i<size;i++){
        printf("%d\n",t[i]);
    }
}

int main(void){
    int t[5]={0,1,2,3,4};
    appliquer_tableau(fois_deux,t,5);
    affiche_tab(t,5);
    return 0;
}
