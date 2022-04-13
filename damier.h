#ifndef DAMIER_H
#define DAMIER_H

/*
    Dans ce module, on g�re la communication avec l'utilisateur. ie l'entr�e des d�placements et des commandes
    du jeu

*/

#include "affichage.h"
#include "dames.h"
#include "jeu.h"

//Fonction initialisant le jeu
void init_damier(damier* jeu);

/*
	Fonctions g�rant l'affichage des choix possibles*
*/

//Fonction qui affiche une rafle
void affiche_rafle(listeCases rafle);

//Fonction qui affiche le liste de coups possibles
void affiche_choixcoup(listeCases* rafle, int n, int couleur, damier* jeu);


/*
        Fonctions de deplacement et de saisie
*/

//Gere la saisie du joueur : d�placement d'un pion ou action
int selec_pion(int couleur,damier* jeu);

//Fonction qui lit un d�placement
int lecture_deplacement(deplacement* d,damier* jeu,int couleur);


/*
	Fonctions de test de la validit� d'une case ou d'un d�placement
*/

//Test si un d�placement est bon
int test_deplacement(int couleur,deplacement d,int damier[10][10]);

//Test si une case est bonne
int test_case(Case c);

// Fonction g�rant le tour d'un joueur
int tour_joueur(damier* jeu,int* couleur,int n,listeCases* rafle,int coup);

#endif
