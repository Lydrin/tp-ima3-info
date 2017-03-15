#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp1.h"

int lire_date(Date* ptr_date)
{

    //Permet de lire une date entrée au clavier
    //printf("Entrez la date sous la forme jj mm aaaa :\n");
    if(scanf("%d%d%d",&(ptr_date->j),&(ptr_date->m),&(ptr_date->a))==EOF){
        return EOF;
    }
    return 0;
}

void affiche_date(Date* ptr_date)
{
    printf("%d/%d/%d\n",ptr_date->j,ptr_date->m,ptr_date->a);
}

int lire_personne(Personne* ptr_personne)
{
    //Return 1 si problèmme dans la lecture de la personne, sinon 0
    ptr_personne->nom = (char *)malloc(LENGTH*sizeof(char));
    ptr_personne->prenom = (char *)malloc(LENGTH*sizeof(char));
    ptr_personne->numero = (char *)malloc(NUMERO*sizeof(char));
    if(scanf("%s",ptr_personne->nom)==EOF)
        return 1;
    if(scanf("%s",ptr_personne->prenom)==EOF)
        return 1;
    if(lire_date(&(ptr_personne->naissance))==EOF)
        return 1;
    if(scanf("%s",ptr_personne->numero)==EOF)
        return 1;
    return 0;
}

void affiche_personne(Personne* ptr_personne)
{
    printf("Nom :%s\n",ptr_personne->nom);
    printf("Prenom :%s\n",ptr_personne->prenom);
    printf("Numero de telephone :%s\n",ptr_personne->numero);
    printf("Date de naissance :");
    affiche_date(&(ptr_personne->naissance)); 
}

void construire_annuaire(Annuaire* ptr_annuaire)
{
    int i=0;
    ptr_annuaire->liste_personne=(Personne *)malloc(MAX_PERSONNES*sizeof(Personne));
    ptr_annuaire->dernier =-1;
    while((i<MAX_PERSONNES) && (lire_personne((ptr_annuaire->liste_personne)+i) != 1)){
        ptr_annuaire->dernier+=1;
        i++;
    }
}

void affiche_annuaire(Annuaire* ptr_annuaire)
{
    int i;
    for(i=0;i<=ptr_annuaire->dernier;i++)
    {
        printf("-----------------------------------------\n");
        affiche_personne(ptr_annuaire->liste_personne+i);
    }
}

int compare_date(Date *d1, Date *d2)
{
    if(d1->a == d2->a && d1->m == d2->m && d1->j == d2->j)
    {
        return 0;
    }

    else
    {
        if(d1->a < d2->a)
        {
            return -1;
        }
        else if(d1->a == d2->a)
        {
            if(d1->m < d2->m)
            {
                return -1;
            }
            else if(d1->m == d2->m)
            {
                if(d1->j < d2->j)
                {
                    return -1;
                }

                else
                {
                    return 1;
                }
            }
        }

    }

    return 1;
}

void tri_annuaire_date(Annuaire *a)
{
	int i,j;
	for(i=a->dernier;i>=1;i--)
	{
		for(j=0;j<i;j++)
		{
			if (compare_date(&((a->liste_personne+j)->naissance),&((a->liste_personne+j+1)->naissance))==1)
			{
				permuter(a->liste_personne+j,a->liste_personne+j+1);
			}
		}
	}
}

void tri_annuaire_nom(Annuaire *a)
{
	int i,j;
	for(i=a->dernier;i>=1;i--)
	{
		for(j=0;j<i;j++)
		{
			if (strcmp((a->liste_personne+j)->nom,(a->liste_personne+j+1)->nom)>0)
			{
				permuter(a->liste_personne+j,a->liste_personne+j+1);
			}
		}
	}
	
}

void permuter(Personne *p1, Personne *p2)
{
	Personne temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}



int main(void)
{
    Annuaire annuaire;
    construire_annuaire(&annuaire);
    affiche_annuaire(&annuaire);
    printf("\n\n\n ***********************************\n\n\n");
    tri_annuaire_nom(&annuaire);
    affiche_annuaire(&annuaire);
    return 0;
}
