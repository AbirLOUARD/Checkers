#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "structures.h"

/*
          Fonctions gérant les commandes de jeu
*/

// Affiche la liste des commandes possibles.
int affiche_aide();
// Fonction appelée lorsque le joueur décide de quitter le jeu.
int affiche_quitter();
// Charge une partie à partir d'un fichier
int affiche_load(damier* jeu);
// Sauvegarde dans un fichier la partie
int affiche_sauver(damier* jeu,int couleur);
// Ré-affiche la plateau
int affiche_plateau(int plateau[10][10]);
//revisualiser une partie

int affiche_revisualiser(damier* jeu);
//sauve temp_reel
void sauver_temps_reel(damier* jeu,int couleur);
// fonction pour les stat
void affiche_stat();
// fonction pour sauvegarder les deplacements
void details_joueurs();

// afficher statistique
/*
          Fonctions affichant le damier
*/

//Fonction qui affiche le damier
void affiche_damier(int damier[10][10]);

//Fonction qui affiche la ligne i du damier
void affiche_ligne(int i,int damier[10][10]);

#endif
