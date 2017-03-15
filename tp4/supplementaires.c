#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

struct Cellule {
    struct Cellule* suiv;
    int val;
};
typedef struct Cellule Cellule;

void ajout_tete(Cellule** l, int val) {
    Cellule* p;
    p = (Cellule *)malloc(sizeof(Cellule));
    p->val = val;
    p->suiv = *l;
    *l = p;
}

void imprimer(Cellule* l) {
    while (l != NULL) {
        printf("%d\n", l->val);
        l = l->suiv;
    }
}

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

int inserer(Cellule** p, int val) {
    Cellule* l = *p;
    if (l == NULL) {
        ajout_tete(p, val);
        return EXIT_SUCCESS;
    }
    while (l->suiv != NULL && l->val < val) {
        p = &l->suiv;
        l = l->suiv;
    }
    if (l->val == val) {
        return EXIT_FAILURE;
    } else if (l->val < val) {
        p = &l->suiv;
    }
    ajout_tete(p, val);
    return EXIT_SUCCESS;
}

// ↓ Spécifique aux questions supplémentaires ↓

bool contient_element(Cellule* l, int el) {
    while (l != NULL) {
        if (el == l->val) {
            return true;
        }
        l = l->suiv;
    }
    return false;
}

bool contient_doublons(Cellule *l) {
    Cellule *i = l;
    while (i != NULL) {
        if (contient_element(i->suiv, i->val)) {
            return true;
        }
        i = i->suiv;
    }
    return false;
}

// Réutilise inserer, mais recrée une copie de
// la liste en mémoire
bool contient_doublons2(Cellule *l) {
    Cellule* copieTriee = NULL;
    int ret;
    while (l != NULL) {
        ret = inserer(&copieTriee, l->val);
        if (ret != EXIT_SUCCESS) {
            desallouer(&copieTriee);
            return true;
        }
        l = l->suiv;
    }
    desallouer(&copieTriee);
    return false;
}

// Concatène les deux listes en les triant, ayant pour
// effet de vérifier plus rapidement si un élément
// est déjà présent
Cellule* union_liste(Cellule *e1, Cellule *e2) {
    Cellule* u = NULL;
    while (e1 != NULL) {
        inserer(&u, e1->val);
        e1 = e1->suiv;
    }
    while (e2 != NULL) {
        inserer(&u, e2->val);
        e2 = e2->suiv;
    }
    return u;
}

// Concatène les deux listes en vérifiant si un élément
// est déjà présent auquel cas il n'est pas ajouté
Cellule* union_liste2(Cellule *e1, Cellule *e2) {
    Cellule* u = NULL;
    while (e1 != NULL) {
        if (!contient_element(u, e1->val)) {
            ajout_tete(&u, e1->val);
        }
        e1 = e1->suiv;
    }
    while (e2 != NULL) {
        if (!contient_element(u, e2->val)) {
            ajout_tete(&u, e2->val);
        }
        e2 = e2->suiv;
    }
    return u;
}

// Suppose que les deux listes n'ont pas déjà des doublons,
// permettant d'éviter certains tests
Cellule* union_liste3(Cellule *e1, Cellule *e2) {
    Cellule* u = NULL;
    while (e1 != NULL) {
        ajout_tete(&u, e1->val);
        e1 = e1->suiv;
    }
    while (e2 != NULL) {
        if (!contient_element(e1, e2->val)) {
            ajout_tete(&u, e2->val);
        }
        e2 = e2->suiv;
    }
    return u;
}

Cellule* intersection_liste(Cellule *e1, Cellule *e2) {
    Cellule* i = NULL;
    while (e1 != NULL) {
        if (contient_element(e2, e1->val)) {
            ajout_tete(&i, e1->val);
        }
        e1 = e1->suiv;
    }
    return i;
}

// Réutilise inserer pour trier la liste et ainsi
// éviter de comparer avec toute la liste à chaque fois
Cellule* ensemble(Cellule *l) {
    Cellule* e = NULL;
    while (l != NULL) {
        inserer(&e, l->val);
        l = l->suiv;
    }
    return e;
}

// Teste tous les éléments déjà inserés
Cellule* ensemble2(Cellule *l) {
    Cellule* e = NULL;
    while (l != NULL) {
        if (!contient_element(e, l->val)) {
            ajout_tete(&e, l->val);
        }
        l = l->suiv;
    }
    return e;
}

// Pour simplifier l'affichage
void details(Cellule *l, char nom) {
    printf("\nListe %c :\n", nom);
    imprimer(l);
    if (contient_doublons(l)) {
        printf("→ Contient un ou plusieurs doublons\n");
    } else {
        printf("→ Ne contient pas de doublons\n");
    }
}

int main() {

    Cellule* l = NULL;
    ajout_tete(&l, 1);
    ajout_tete(&l, 2);
    ajout_tete(&l, 3);
    ajout_tete(&l, 4);
    details(l, 'l');

    Cellule* m = NULL;
    ajout_tete(&m, 3);
    ajout_tete(&m, 4);
    ajout_tete(&m, 5);
    ajout_tete(&m, 5);
    ajout_tete(&m, 6);
    details(m, 'm');

    Cellule* u = union_liste(l, m);
    details(u, 'u');

    Cellule* i = intersection_liste(l, m);
    details(i, 'i');

    Cellule* e = ensemble(m);
    details(e, 'e');

    desallouer(&l);
    desallouer(&m);
    desallouer(&u);
    desallouer(&i);
    desallouer(&e);
    return EXIT_SUCCESS;
}
