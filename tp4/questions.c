#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

// 2.1.1
struct Cellule {
    struct Cellule* suiv;
    int val;
};
typedef struct Cellule Cellule;

// 2.1.2
void ajout_tete(Cellule** l, int val) {
    Cellule* p;
    p = (Cellule *)malloc(sizeof(Cellule));
    p->val = val;
    p->suiv = *l;
    *l = p;
}

// 2.1.3
void imprimer(Cellule* l) {
    while (l != NULL) {
        printf("%d\n", l->val);
        l = l->suiv;
    }
}

// 2.1.4
bool est_trie(Cellule* l) {
    if (l == NULL) {
        return true;
    }
    int temp;
    while (l->suiv != NULL) {
        temp = l->val;
        l = l->suiv;
        if (l->val < temp) {
            return false;
        }
    }
    return true;
}

// 2.1.5
void supprimer_tete(Cellule** l) {
    Cellule* p;
    p = (*l)->suiv;
    free(*l);
    *l = p;
}

// 2.1.6
// Méthode itérative
void desallouer(Cellule** l) {
    if (*l==NULL){
        return;
    }
    Cellule* next;
    Cellule* current = *l;
    while (current != NULL) { //Oui Anthony ca marche
        next = current->suiv;
        free(current);
        current = next;
    }
}

// Méthode itérative, réutilise supprimer_tete
void desallouer2(Cellule** l) {
    if (*l == NULL) {
        return;
    }
    while ((*l)->suiv != NULL) {
        supprimer_tete(l);
    }
    free(*l);
}

// Méthode réccursive
void desallouer3(Cellule** l) {
    if (*l == NULL) {
        return;
    }
    desallouer(&(*l)->suiv);
    free(*l);
}


// 2.2.1
void inserer(Cellule** p, int val) {
    Cellule* l = *p;
    if (l == NULL) {
        ajout_tete(p, val);
        return;
    }
    while (l->suiv != NULL && l->val < val) {
        p = &l->suiv;
        l = l->suiv;
    }
    if (l->val == val) {
        return;
    } else if (l->val < val) {
        p = &l->suiv;
    }
    ajout_tete(p, val);
}

// 2.2.2
Cellule* lire_fichier(FILE * fp) {
    Cellule* l = NULL;
    int val;
    while (fscanf(fp, "%d", &val) != EOF) {
        inserer(&l, val);
    }
    return l;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Mode test de la partie 2.1.\n");
        printf("(pour tester la partie 2.2, utilisez : %s FICHIER_ENTREE)\n", argv[0]);

        // 2.1.7
        Cellule* l = NULL;
        ajout_tete(&l, 42);
        ajout_tete(&l, 40);
        ajout_tete(&l, 43);
        imprimer(l);
        printf("Est triée : %d\n", est_trie(l));
        supprimer_tete(&l);
        imprimer(l);
        printf("Est triée : %d\n", est_trie(l));
        desallouer(&l);

    } else {
        printf("Mode test de la partie 2.2.\n");
        printf("(pour tester la partie 2.1, utilisez : %s)\n", argv[0]);

        FILE* fp;
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            printf("Impossible d'ouvrir le fichier %s.\n", argv[1]);
            return EXIT_FAILURE;
        }

        Cellule * l = lire_fichier(fp);

        fclose(fp);

        imprimer(l);
        if (est_trie(l)) {
            printf("La liste est correctement triée.\n");
        } else {
            printf("Erreur: La liste n'est pas correctement triée.\n");
            return EXIT_FAILURE;
        }
        desallouer(&l);
    }

    return EXIT_SUCCESS;
}
