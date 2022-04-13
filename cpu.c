#ifndef CPU_C
#define CPU_C

/*
	Dans ce module (cpu.c,cpu.h), on définit les fonctions permettant de faire jouer l'ordinateur.
	Ces fonctions sont utilisées pour determiner, si la partie est terminée, on a également ajouté
	les fonctions traitant de ce problème dans ce module.

*/

#include "cpu.h"
/*
	Renvoie un deplacement, si la dame en (i,j) peut bouger, 0 sinon

	param:
		plateau : matrice contenant les pions du jeu
		i,j : ligne et colonne de la pièce a bouger
		couleur : indique la couleur des pions de l'ordinateur

*/

deplacement* testdeplacement_dame(int plateau[10][10],int i,int j,int couleur) {
deplacement* d = (deplacement*) malloc (sizeof(deplacement));

	if(i - 1 >= 0 && j-1 >=0 && plateau[i-1][j-1] == CASE_VIDE) {
		//printf("Case vide");
		d->case_i.lig=i;
		d->case_i.col=j;
		d->case_f.lig=i-1;
		d->case_f.col=j-1;
		return d;
	}

	if(i - 1>= 0 && j + 1 < 10 && plateau[i-1][j+1] == CASE_VIDE) {
		d->case_i.lig=i;
		d->case_i.col=j;
		d->case_f.lig=i-1;
		d->case_f.col=j+1;
		return d;
	}

	if(i + 1 < 10 && j + 1 < 10 && plateau[i+1][j+1] == CASE_VIDE) {
		d->case_i.lig=i;
		d->case_i.col=j;
		d->case_f.lig=i+1;
		d->case_f.col=j+1;
		return d;
	}

	if(i + 1 < 10 && j - 1 >=0 && plateau[i+1][j-1] == CASE_VIDE) {
		d->case_i.lig=i;
		d->case_i.col=j;
		d->case_f.lig=i+1;
		d->case_f.col=j+1;
		return d;
	}
	return 0;
}

/*
	Renvoie un deplacement, si le pion en (i,j) peut bouger, 0 sinon

	param:
		plateau : matrice contenant les pions du jeu
		i,j : ligne et colonne de la pièce a bouger
		couleur : indique la couleur des pions de l'ordinateur

*/

deplacement* testdeplacement(int plateau[10][10],int i,int j,int couleur) {
deplacement* d = (deplacement*) malloc (sizeof(deplacement));

	if(i - couleur >= 0 && i - couleur < 10 && j+1 <10 && plateau[i-couleur][j+1] == CASE_VIDE) {
		//printf("Case vide");
		d->case_i.lig=i;
		d->case_i.col=j;
		d->case_f.lig=i-couleur;
		d->case_f.col=j+1;
		return d;
	}

	if(i - couleur >= 0 && i - couleur < 10 && j-1 >= 0 && plateau[i-couleur][j-1] == CASE_VIDE) {
		d->case_i.lig=i;
		d->case_i.col=j;
		d->case_f.lig=i-couleur;
		d->case_f.col=j-1;
		return d;
	}
	return 0;
}

/*
	Fonction qui renvoie le premier coup possible

	param:
		jeu : structure damier
		couleur : indique la couleur des pions de l'ordinateur

*/

listeCases trouvercoup(damier* jeu, int couleur) {
int i=0,j,nbpion=0,max;
deplacement *d;
listeCases coup = (listeCases) malloc(sizeof(struct element));
if(couleur == PION_BLANC)
	max = jeu->nb_blanc;
else max = jeu->nb_noir;

while(nbpion<max) {
	for(j=0;j<10;j++) {
		if(jeu->plateau[i][j] == couleur) {
			//On a trouvé un pion
			nbpion++;
			if((d=testdeplacement(jeu->plateau,i,j,couleur)) !=0) {
			//On cree notre liste
				coup->c = d->case_i;
				coup->suivante = (listeCases) malloc(sizeof(struct element));
				coup->suivante->c = d->case_f;
				coup->suivante->suivante = 0;
				return coup;
			}
		}
		else {
			if(jeu->plateau[i][j] == 2*couleur) {
				//On a trouvé une dames
				nbpion++;
				if((d=testdeplacement_dame(jeu->plateau,i,j,couleur)) !=0) {
				//On cree notre liste
					coup->c = d->case_i;
					coup->suivante = (listeCases) malloc(sizeof(struct element));
					coup->suivante->c = d->case_f;
					coup->suivante->suivante = 0;
					return coup;
				}
			}
		}
	}
	i++;
}

return 0;
}


/*
	Fonction qui fait jouer l'ordinateur

	return : -1 si l'ordinateur ne peut plus jouer.
	          1 sinon
	param:
		jeu : structure damier
		couleur : indique la couleur des pions de l'ordinateur
		nb_coup : indique le nb_coup obligatoire possible
		rafle : tableau des listes de coups possible
*/

int jouer_cpu(damier* jeu,int couleur,int nb_coup,listeCases* rafle) {
listeCases coup;
deplacement d;
	//Si il ya plusieurs coups possibles, on prend le premier
	if(nb_coup>0)
		faire_coup(rafle[0],couleur,jeu);
	else {
		//Pas de coup possible
		if((coup=trouvercoup(jeu,couleur))==0)
			return -1;
		else {
			d.case_i = coup->c;
			d.case_f = coup->suivante->c;
			deplace_pion(couleur,d,0,jeu);
		}

	}
	sauver_temps_reel(jeu,couleur);
	return 1;
}

/*
	Fonction qui vérifie si la partie est finie

	return : la couleur des pions du gagnant.
	         0 si la partie n'est pas finie
*/

int jeu_fini(damier* jeu, int couleur) {
	if(jeu->nb_blanc==0)
	  {
        affiche_sauver(jeu,couleur);
		return PION_BLANC;
		}
	if(jeu->nb_noir==0)
	{
        affiche_sauver(jeu,couleur);
		return PION_NOIR;
    }

	if(trouvercoup(jeu,couleur) == 0) {
		printf("Fin du match\n");
		affiche_sauver(jeu,couleur);
		affiche_damier(jeu->plateau);
		if(couleur == PION_NOIR)
		{
            affiche_sauver(jeu,couleur);
            printf("Les noirs ne peuvent plus bouger !\n");
		}
		else
		{
            affiche_sauver(jeu,couleur);
             printf("Les blancs ne peuvent plus bouger !\n");
		}
		return couleur;
	}
	return 0;

}


#endif
