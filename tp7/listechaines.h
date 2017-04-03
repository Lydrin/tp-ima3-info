#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#define MAXSIZE 30

//Declaration de liste chainee de chaines de caracteres
typedef struct cell {
  char val[MAXSIZE];
  struct cell * suiv;
} Cellule, *Ptcellule, *Liste;

//Affichage de la liste en ligne
void afficher_liste(Liste);

//Ajout d'un mot en tete de la liste
void ajout_tete(Liste *, char *mot);

//Suppression du mot en tete de la liste
void supprimer_tete(Liste *);

//Destruction de Liste.
void desallouer(Liste*);

bool est_triee(Liste);
