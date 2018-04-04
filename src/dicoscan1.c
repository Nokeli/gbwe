#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dicoscan.h"

int getSynLine1(const char* word,char* line,const char *base) //copie dans la chaine 'line', la ligne du dictionnaire associ�e au mot 'word'
// retourne un nombre positif en cas de succes, negatif en cas d'echec
{
        FILE* findex;
        FILE *fo_err;
        char num[256]; //temporaire : contient un nombre sous forme de chaine de carat�res
        int i=0; //variable de boucle
        int fg=0,fd=0; //fils gauche et droit
        int dicopos=0; //position de la premi�re lettre du mot dans le dictionnaire
        int cmp=0; //temporaire
        //rmq : on se sert aussi de 'line' comme d'une chaine temporaire contenant le mot en cours dans l'arbre
        char filename[256];
        //sabine
fo_err=fopen("../../html/java/data/erreur.dat","ab");
fprintf(fo_err,"recherche %s %s\n",word,base);
fclose(fo_err);
        sprintf(filename,"index.arb.%s",base);
        findex=fopen(filename,"rb");
        
        if (findex==NULL)
			
                        {printf("pas d'index");
                        return -1;}
        //parcours dans l'arbre de recherche
        do
        {
                i=0;
                do //lecture du mot en cours dans l'arbre
                {
                        line[i]=fgetc(findex);
                        i++;
                }while (line[i-1]!=':');
                line[i-1]=0;
                i=0;

                do //lecture de la position du mot dans le dico
                {
                        num[i]=fgetc(findex);
                        i++;
                }while (num[i-1]!=':');
                num[i-1]=0;
                sscanf(num,"%d",&dicopos);
                i=0;
                do //lecture de la position du fils gauche dans l'arbre
                {
                        num[i]=fgetc(findex);
                        i++;
                }while (num[i-1]!=':');
                num[i-1]=0;
                sscanf(num,"%d",&fg);
                i=0;
                do //lecture de la position du fils droit dans l'arbre
                {
                        num[i]=fgetc(findex);
                        i++;
                }while (num[i-1]!='\n');
                num[i-1]=0;
                sscanf(num,"%d",&fd);
                cmp=strcmp(line,word);
                if (cmp>0)
                { // le mot recherch� est dans la branche gauche
                        if (fg==0) // pas de fils gauche => mot inconnu => pas d'entr�e dans dico => pas de synonymes
                        {
                                sprintf(line,"%s\t:\t",word);
                                printf(line,"pas d'entree %s\t:\t",word);
                                return 0;
                        }
                        fseek(findex,fg,0);
                }
                if (cmp<0)
                { // le mot recherch� est dans la branche droite
                        if (fd==0) // pas de fils droit => mot inconnu => pas d'entr�e dans dico => pas de synonymes
                        {
                                sprintf(line,"%s\t:\t",word);
                                printf(line,"pas de fils %s\t:\t",word);
                                return 0;
                        }
                        fseek(findex,fd,0);
                }
        }while(cmp!=0);
        //mot trouv� (donc line=word)

        fclose(findex);

        //lecture de 'line' dans le dico
        sprintf(filename,"vs_dicos.%s",base);
        findex=fopen(filename,"rb");
        
        
        if (findex==NULL)
        	{printf("pas de dico");return -2;}
        fseek(findex,dicopos,0);
        i=0;
        do
        {
                line[i]=fgetc(findex);
                i++;
        }while (line[i-1]!=10);
        line[i-1]=0;
	/*
        if (i>MAX_LINE_LEN)
        	return -3;
	*/
       fclose(findex);
       fo_err=fopen("../../html/java/data/erreur.dat","ab");
fprintf(fo_err,"recherche %s %s\n",word,line);
fclose(fo_err);
        return 1;
}

