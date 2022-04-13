 #ifndef STRUCTURES_H
 #define STRUCTURES_h

#include<stdio.h>
#include<stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include<string.h>

#define PION_BLANC 1
#define DAME_BLANC 2

#define PION_NOIR -1
#define DAME_NOIR -2

#define CASE_VIDE  0

#define HUMAIN 0
#define CPU 1
int nivau;
char file_sav[50];

 typedef struct{
	int lig,col;
} Case;

typedef struct{
	Case case_i,case_f;
} deplacement;


typedef struct element *listeCases;
struct element {
	Case c;
	listeCases suivante;
};


typedef struct {
	char *nom;
	int type; // HUMAIN ou CPU
	int couleur; //PION_BLANC ou PION_NOIR

}joueur;

typedef struct{
	int plateau[10][10]; //Represente l'état du plateau
	int nb_noir; //Represente le nombre de pion noir
	int nb_blanc; //Represente le nombre de pion blanc
}damier;

typedef struct {
	char nomG[10];
	char nomP[10];
	char pionG[10];
	char niveau[10];
}Victoire;

//joueur_c contient l'adresse du joueur dont c'est le tour.
joueur *joueur1,*joueur2,*joueur_c;
#endif
