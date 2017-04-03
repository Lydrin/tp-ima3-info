/*Source Code From Laure Gonnord, 2012*/
/*Adapted from Bernard Carre, 2011*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*List library : reminder, the word have maximal size  MAXSIZE*/
#include "listechaines.h"

/*Size of the hashtables */
#define TABLE_SIZE 10

/**Hash functions**/
int asciis(char *word)
{
  int i=0;
  int h=0;
  while(word[i]!='\0')
    {
      h=h+(word[i]-96);
      i++;
    }
  return h;
}

int hash(char *word)
{
  return (asciis(word) % TABLE_SIZE);
}

/*Declaration of type Hashtable */
typedef Liste Hashtable[TABLE_SIZE];


/*Initialisation of a given Hashtable*/
void init_ht(Hashtable ht) {
    int i;
    for(i=0;i<TABLE_SIZE;i++){
        ht[i]=NULL;
    } 
}

/*Update of the hashtable : add the given word in the table!*/
void update_ht(char *word, Hashtable ht) {
    int indice = hash(word);
    ajout_alphab(&(ht[indice]),word);
}

/*Load the file in the internal structure ht */
void load_ht(FILE *fp, Hashtable ht) {
    char word[MAXSIZE];
    while(fscanf(fp,"%s",word)!=EOF){
       update_ht(word,ht);
    } 
}

void print_ht(Hashtable ht){
    for(int i=0;i<TABLE_SIZE;i++){
        afficher_liste(ht[i]);
    }
}

/*Count the collisions*/
void collisions(Hashtable ht) {
    
}

/*Maximal hash of the words of the given file*/
/*returns max_word such that hash(max_word)=hmax*/
void max_hash(FILE *fp, char *max_word, int *hmax) {
  //TODO
}

/*Main function*/
int main (int argc, char *argv[]) {
  if (argc < 2) { // text file is missing ?
    fprintf(stderr, "usage: hash <file_name>\n");
  } else {
    FILE *fp;
    fp=fopen(argv[1], "r");
    if (fp==NULL) {
      fprintf(stderr, "no such file, or unreachable: %s\n", argv[1]);
    } else {
      //using lists !
      Hashtable ht;
      init_ht(ht);
      load_ht(fp,ht); 
      print_ht(ht);


      // replace by declaration and use of hashtables!
      //TODO !


      printf("Fin de traitement!\n");
    }//end of else
  }

  return 0;
}
