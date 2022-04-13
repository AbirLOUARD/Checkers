#ifndef DAMES_H
#define DAMES_H

/*
       Ce module est consacré aux fonctions liées au déplacement des dames, mais aussi a la recherche
       de la rafle maximale pour une dame.

*/

#include "affichage.h"

//Recopie la structure du jeu pour effectuer les simulations de coup
damier copie_damier(damier* jeu);

//Fonction appelée à chaque fin de tour qui promoue un pion en dame
void faire_dames(damier* jeu,int couleur);

//Vérifie si le deplacement d est valide
int test_deplace_dame(damier* jeu, int couleur,deplacement d);

//Deplace la dame suivant d, en prenant le pion situé en prise
void deplace_dame(damier* jeu, int couleur,deplacement d, int p, Case prise);

// Fonction qui regarde combien de pions la dames en ca peut prendre, et les stockes dans les tableaux de cases : d et a
int prise_possible(damier* jeu,int couleur,Case ca,Case* d,Case* a);

//Renvoie dans n_case la liste des possibilités de prises d'une dame a partir c,l suivant la direction ic,il
int dame_prise(int c,int l,int ic,int il,int couleur,int plateau[10][10],Case* n_case, Case* direction);

//Fonction calculant le nombre de prises max a partir de case_i
int max_dame_prises(Case case_i, Case sens, int couleur, damier* jeu, listeCases* rafle_max,int* n);

//Fonction qui calcule le coup obligatoire pour la dame, et adapte les tableaux de rafles r et pr, en fonction
// du resultat, ainsi que le nombre de façon de faire : n
void dame(int l, int c,int* nb_pion,int* max,int *n,int couleur,damier jeu,listeCases* pr,listeCases* r);
#endif
