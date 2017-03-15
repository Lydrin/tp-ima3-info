#include <stdlib.h>
#include <string.h>
#include "tp2.h"

int lire_date(FILE* fp, Date* date)
{
    if(fscanf(fp,"%d %d %d",&(date->j),&(date->m),&(date->a))==EOF)
    {
        return EOF;
    }
    return 0;
}

int construire_annuaire(FILE *fp, Annuaire* a)
{
    int i=0;
    a->dernier=-1;
    while(i<MAX_PERSONNES && lire_personne(fp,a->liste_personne+i)!=1)
    {
        a->dernier+=1;
        i++;
    }
    return 0;
}

int lire_personne(FILE * fp,Personne* ptr_pers)
{
    ptr_pers->nom=(char *)malloc(LENGTH*sizeof(char));
    ptr_pers->prenom=(char *)malloc(LENGTH*sizeof(char));
    ptr_pers->numero=(char *)malloc(NUMERO*sizeof(char));

    if(fscanf(fp,"%s",ptr_pers->nom)==EOF)
    {
        return 1;
    }
    if(fscanf(fp,"%s",ptr_pers->prenom)==EOF)
    {
        return 1;
    }
    if(lire_date(fp, &(ptr_pers->naissance))==EOF)
    {
        return 1;
    }
    if(fscanf(fp,"%s",ptr_pers->numero)==EOF)
    {
        return 1;
    }
    return 0;
}

void affiche_date(Date *date)
{
    printf("Jour : %d \n", date->j);
    printf("Mois : %d \n", date->m);
    printf("Annee: %d \n", date->a);
}

void affiche_personne(Personne *p)
{
    printf("Nom : %s \n",p->nom);
    printf("Prenom : %s \n",p->prenom);
    affiche_date(&(p->naissance));
    printf("Numero : %s \n\n",p->numero);
}

void affiche_annuaire(Annuaire *a)
{
	int i;
	for(i=0;i<=(a->dernier);i++)
	{
		printf("---------------------------------------\n");
		affiche_personne(a->liste_personne+i);
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

int rech_dicho(char* name, Annuaire* annuaire, int min, int max)
{
	if(max<min)
	{
		return -1;
	}
	int moy = (max+min)/2;
	if (strcmp((annuaire->liste_personne+moy)->nom,name)==0)
	{
		return moy;
	}
	else if(strcmp((annuaire->liste_personne+moy)->nom, name)>0)
	{
		return rech_dicho(name, annuaire, min, moy-1);
	}
	else
	{
		return rech_dicho(name, annuaire, moy+1, max);
	}
}

void recherche_personne(char* name, Annuaire* annuaire)
{
    int rech = rech_dicho(name,annuaire,0,annuaire->dernier);
    if(rech==-1)
    {
        printf("La personne n'est pas référencée dans l'annuaire\n");
    }
    else
    {
        affiche_personne(annuaire->liste_personne+rech);
    }
}

void permuter(Personne *p1, Personne *p2)
{
	Personne temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

int modifier_numero(Annuaire* annuaire,char* nom, char* number)
{
    int rech = rech_dicho(nom,annuaire,0,annuaire->dernier);
    if(rech!=-1) {
        (annuaire->liste_personne+rech)->numero = number;
    }
    else
    {
        printf("Cette personne n'existe pas dans l'annuaire \n");
    }
    return rech;
}

void save_annuaire(FILE* fp, Annuaire* annuaire)
{
    int i;
    for(i=0;i<=annuaire->dernier;i++)
    {
        fprintf(fp,"%s\n",(annuaire->liste_personne+i)->nom);
        fprintf(fp,"%s\n",(annuaire->liste_personne+i)->prenom);
        fprintf(fp,"%d\n",(annuaire->liste_personne+i)->naissance.j);
        fprintf(fp,"%d\n",(annuaire->liste_personne+i)->naissance.m);
        fprintf(fp,"%d\n",(annuaire->liste_personne+i)->naissance.a);
        fprintf(fp,"%s\n",(annuaire->liste_personne+i)->numero);
    }
}

int main(int argc, char* argv[])
{
    FILE* fp=fopen("annu.txt","r");
    FILE* fsave;
    Annuaire annuaire;
    construire_annuaire(fp,&annuaire);
    char* name = (char*)malloc(LENGTH*sizeof(char));
    char* number=(char*)malloc(NUMERO*sizeof(char));
    char* file_name = (char*)malloc(LENGTH*sizeof(char));
    int quitter = 0;
    int save =2;
    printf("==========ANNUAIRE.IO==========\n");
    while(quitter!=1)
    {
        int choix =42;
        while(choix <=0 || choix>6)
        {
            printf("1. Afficher l'annuaire\n");
            printf("2. Recherche d'une personne\n");
            printf("3. Modification du numero de telephone\n");
            printf("4. Tri de l'annuaire\n");
            printf("5. Sauvegarde de l'annuaire\n");
            printf("6. Quitter\n");
            printf("Votre choix :\n");
            scanf("%d",&choix);
        } 
        switch(choix)
        {
            case 1:
                affiche_annuaire(&annuaire);
                break;
            case 2:
                printf("\n");
                printf("Entrez le nom de la personne à rechercher:\n");
                scanf("%s",name);
                recherche_personne(name,&annuaire);
                break;
            case 3:
                printf("\n");
                printf("Entrez le nom :\n");
                scanf("%s",name);
                printf("Entrez le nouveau numero:\n");
                scanf("%s",number);
                modifier_numero(&annuaire, name, number);
                break;
            case 4:
                printf("\n");
                tri_annuaire_nom(&annuaire);
                printf("Annuaire trié\n\n");
                break;
            case 5:
                printf("\n");
                printf("Entrez le nom du fichier de l'annuaire :\n");
                scanf("%s",file_name);
                fsave=fopen(file_name,"w");
                save_annuaire(fsave, &annuaire);
                break;
            case 6:
                printf("\n");
                while(save<0 || save>1)
                {
                    printf("Voulez vous sauvegardez avant de quitter ?\n");
                    scanf("%d",&save);
                }
                if(save==1)
                {
                    printf("Entrez le nom du fichier de l'annuaire:\n");
                    scanf("%s",file_name);
                    fsave=fopen(file_name,"w");
                    save_annuaire(fsave,&annuaire);
                }
                quitter = 1;
                break;

        }
    }
}

