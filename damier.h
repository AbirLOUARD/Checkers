#ifndef DAMIER_H
#define DAMIER_H

/*
    Dans ce module, on gère la communication avec l'utilisateur. ie l'entrée des déplacements et des commandes
    du jeu

*/

#include "affichage.h"
#include "dames.h"
#include "jeu.h"

//Fonction initialisant le jeu
void init_damier(damier* jeu);

/*
	Fonctions gérant l'affichage des choix possibles*
*/

//Fonction qui affiche une rafle
void affiche_rafle(listeCases rafle);

//Fonction qui affiche le liste de coups possibles
void affiche_choixcoup(listeCases* rafle, int n, int couleur, damier* jeu);


/*
        Fonctions de deplacement et de saisie
*/

//Gere la saisie du joueur : déplacement d'un pion ou action
int selec_pion(int couleur,damier* jeu);

//Fonction qui lit un déplacement
int lecture_deplacement(deplacement* d,damier* jeu,int couleur);


/*
	Fonctions de test de la validité d'une case ou d'un déplacement
*/

//Test si un déplacement est bon
int test_deplacement(int couleur,deplacement d,int damier[10][10]);

//Test si une case est bonne
int test_case(Case c);

// Fonction gérant le tour d'un joueur
int tour_joueur(damier* jeu,int* couleur,int n,listeCases* rafle,int coup);

#endif
