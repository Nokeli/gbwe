/* acces_fichier.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "taille_tampon.h"
#include "acces_fichier.h"
#include "erreurs.h"
#include "min.h"

/******************************************************************/
/*         fonctions d'ouverture de fichier en mode (r,w,..)      */
/******************************************************************/

FILE * ouvre_fichier(const char *vedette,char *extension,char *mode)
{
  FILE * flot;
  char pnom[TAILLE_TAMPON];


  flot = malloc(sizeof(FILE *));
  strcpy(pnom,vedette);
  strcat(pnom,extension);

  if ((flot = fopen(pnom,mode)) == NULL )
    {
      if ( *mode == 'r' )
        fprintf(stderr, "%s : impossible de lire %s\n",__FILE__, pnom);
      if ( *mode == 'w' )
        fprintf(stderr, "%s : impossible d'ecrire %s\n",__FILE__, pnom);
      exit(EXIT_FAILURE);
    } 
  return flot;
}

/******************************************************************/
/*         fonctions d'ecriture de fichier en mode (w,..)      */
/******************************************************************/

void ecrit_fichier(const char *vedette, char *extension, char *mode,double **C,int ligne,int colonne)
{
  int i,j;
  int borne;
  FILE *flot;
  
  borne = min_i(7,colonne);
  flot = ouvre_fichier(vedette,extension,mode);  
  for ( j = 2 ; j <= borne ; j++ )
    {
      for( i = 1 ; i <= ligne ; i++ )
        {
          if ( i == ligne )
            fprintf(flot,"%f\n",C[i][j]);
          else
            fprintf(flot,"%f ",C[i][j]);
        }
    }
  fclose(flot);
}







