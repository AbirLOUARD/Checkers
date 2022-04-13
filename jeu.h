#ifndef JEU_H
#define JEU_H

/*
    Dans ce module, nous g�rons la recherche du coup obligatoire, pour les pions toutes les fonctions
    n�cessaire se trouvent dans ce module. En ce qui concerne les dames, nous avons pr�f�r� les mettre
    dans le module r�serv� aux dames : dames.c/dames.h.
    On trouve �galement les fonctions qui d�placent un pion, et effectuent une rafle.

*/


#include "affichage.h"
#include "dames.h"

/*
       Fonctions li�es � la recherche du coup obligatoire
*/
//Fonction renvoyant le coup obligatoire (-1 si pas de coup obligatoire)
int coup_obligatoire(int couleur,damier jeu,listeCases* pr,listeCases* r,int* n);

//Fonction qui calcule le coup obligatoire pour la dame, et adapte les tableaux de rafles r et pr, en fonction
// du resultat, ainsi que le nombre de fa�on de faire : n
void pion(int l, int c,int* nb_pion,int* max,int *n,int couleur,damier jeu,listeCases* pr,listeCases* r);

//Fonction renvoyant les prises possibles a partir de la case c,l
int pion_prise(int c,int l,int couleur,int plateau[10][10],Case* prises);

//Fonction renvoyant le nombre maximum de prises en partant d'une case
int max_pion_prises(Case case_i, int couleur, damier* jeu, listeCases* rafle_max, int* n);


//Fonction qui d�place un pion
void deplace_pion(int couleur,deplacement d,int prise,damier* jeu);

//Fonction qui effectue une rafle
void faire_coup(listeCases rafle,int couleur, damier* jeu);

#endif

