#include<stdlib.h>

#define LENGTH 20
#define NUMERO 10
#define MAX_PERSONNES 100

typedef struct{
    int j;
    int m;
    int a;
}Date;

typedef struct{
    char* nom;
    char* prenom;
    char* numero;
    Date naissance;
}Personne;

typedef struct{
    Personne* liste_personne;
    int dernier;
}Annuaire;


int lire_date(Date *ptr_date);
void affiche_date(Date* ptr_date);
int lire_personne(Personne* ptr_personne);
void affiche_personne(Personne* ptr_personne);
void construire_annuaire(Annuaire* ptr_annuaire);
void affiche_annuaire(Annuaire* ptr_annuaire);
void tri_annuaire_date(Annuaire* ptr_annuaire);
void tri_annuaire_nom(Annuaire* ptr_annuaire);
void permuter(Personne* ptr_personne1, Personne* ptr_personne2);
int compare_date(Date* ptr_date1, Date* ptr_date2);
