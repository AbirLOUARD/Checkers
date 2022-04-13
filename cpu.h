#ifndef CPU_H
#define CPU_H

#include "affichage.h"
#include "jeu.h"

//Renvoie un deplacement, si le pion en (i,j) peut bouger, null sinon
deplacement* testdeplacement(int plateau[10][10],int i,int j,int couleur);
//Renvoie un deplacement, si la dame en (i,j) peut bouger, null sinon
deplacement* testdeplacement_dame(int plateau[10][10],int i,int j,int couleur);


//Renvoie le premier coup possible
listeCases trouvercoup(damier* jeu, int couleur);

//Fait jouer l'ordinateur
int jouer_cpu(damier* jeu,int couleur,int nb_coup,listeCases* rafle);

//Fonction verifiant que la partie est finie
int jeu_fini(damier* jeu, int couleur);
#endif
