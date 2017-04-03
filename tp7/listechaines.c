#include"listechaines.h"

void ajout_tete(Cellule** l,char *mot) {
    Cellule* p;
    p = (Cellule *)malloc(sizeof(Cellule));
    strcpy(p->val,mot);
    p->suiv = *l;
    *l = p;
}

void imprimer(Cellule* l) {
    while (l != NULL) {
        printf("%s\n", l->val);
        l = l->suiv;
    }
}

bool est_triee(Cellule* l) {
    if (l == NULL) {
        return true;
    }
    char temp[MAXSIZE];
    while (l->suiv != NULL) {
        strcpy(temp,l->val);
        l = l->suiv;
        if(strcmp(temp,l->val)>0){
            return false;
        }
    }
    return true;
}

void supprimer_tete(Cellule** l) {
    Cellule* p;
    p = (*l)->suiv;
    free(*l);
    *l = p;
}

void desallouer(Cellule** l) {
    Cellule* next;
    Cellule* current = *l;
    while (current != NULL) {
        next = current->suiv;
        free(current);
        current = next;
    }
}


