#include <stdio.h>

#define LENGTH 20
#define NUMERO 10
#define MAX_PERSONNES 100

typedef struct
{
    int j;
    int m;
    int a;
} Date;

typedef struct
{
    char* nom;
    char* prenom;
    char* numero;
    Date naissance;
} Personne;

typedef struct
{
    Personne liste_personne[MAX_PERSONNES];
    int dernier;
} Annuaire;

int construire_annuaire(FILE *fp, Annuaire* a);
int lire_personne(FILE* fp,Personne* personne);
void affiche_date(Date *date);
void affiche_personne(Personne *p);
void affiche_annuaire(Annuaire *a);
int compare_date(Date *d1, Date *d2);
void tri_annuaire_date(Annuaire *a);
void permuter(Personne *p1, Personne *p2);
int rech_dicho(char *name, Annuaire *annuaire, int min, int max);
int modifier_numero(Annuaire* annuaire,char* nom, char* numero);
void save_annuaire(FILE* fp, Annuaire* annuaire);
void recherche_personne(char* name, Annuaire* annuaire);
