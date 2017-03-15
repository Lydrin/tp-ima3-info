#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

struct Cellule {
    struct Cellule* suiv;
    int entier;
    int multiplicite;
};
typedef struct Cellule Cellule;

void ajout_tete(Cellule** l, int val) {
    Cellule* p;
    p = (Cellule *)malloc(sizeof(Cellule));
    p->entier = val;
    p->multiplicite=1;
    p->suiv = *l;
    *l = p;
}

void imprimer(Cellule* l) {
    while (l != NULL) {
        printf("Entier : %d, multiplicité : %d \n", l->entier,l->multiplicite);
        l = l->suiv;
    }
}

void supprimer_tete(Cellule** l) {
    Cellule* p;
    p = (*l)->suiv;
    free(*l);
    *l = p;
}
void inserer(Cellule **l, int val)
{
    if(*l==NULL){
        ajout_tete(l,val);
        return;
    }
    if((*l)->entier == val){
        (*l)->multiplicite +=1;
        return;
    }
        
    if((*l)->entier > val){
        ajout_tete(l,val);
        return;
    }
    inserer(&((*l)->suiv),val);
   
}

Cellule* lire_fichier(FILE * fp) {
    Cellule* l = NULL;
    int val;
    while (fscanf(fp, "%d", &val) != EOF) {
        inserer(&l, val);
    }
    return l;
}

bool est_trie(Cellule *l){
    if(l==NULL || l->suiv == NULL){
        return true;
    }
    if(l->entier > l->suiv->entier){
        return false;
    }
    return est_trie(l->suiv);
}

void supprimer_liste(Cellule **l){
    if(*l==NULL){
        return;
    }
    supprimer_tete(l);
    supprimer_liste(l);
}

int recher_mult(Cellule *l, int val){
    if(l==NULL|| l->entier > val){
        return 0;
    }
    if(l->entier==val){
        return l->multiplicite;
    }
    return recher_mult(l->suiv,val);
}

int cardinal(Cellule *l){
    if(l==NULL){
        return 0;
    }
    return recher_mult(l,l->entier) + cardinal(l->suiv);

}

int main(int argc, char *argv[]){
    Cellule *l=(Cellule *)malloc(sizeof(Cellule));
    if(argc == 2){
        FILE *fp;
        fp = fopen(argv[1],"r");
        l=lire_fichier(fp);
    }
    imprimer(l);
    printf("%d\n",est_trie(l));
    printf("%d\n",recher_mult(l,12));
    printf("%d\n",cardinal(l));
    supprimer_liste(&l);
    imprimer(l);
    return 0;
}
