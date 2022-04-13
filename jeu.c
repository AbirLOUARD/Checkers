#ifndef JEU_C
#define JEU_C

/*
    Dans ce module, nous gérons la recherche du coup obligatoire, pour les pions toutes les fonctions
    nécessaires se trouvent dans ce module. En ce qui concerne les dames, nous avons préféré les mettre
    dans le module réservé aux dames : dames.c/dames.h.
    On trouve également les fonctions qui déplacent un pion, et effectuent une rafle.

*/

#include "jeu.h"

/*
	Fonction gérant la recherche de la rafle maximale pour le pion situé en c,l
	Cette fonction est appelée dans la fonction coup obligatoire qui parcourt tous le damier
	  à la recherche de tous les pions du joueur.
	  param :
	     Entrée:
		 c,l : case ou se trouve la dame
		 jeu : structure du jeu
	     Entrée / Sortie :
		 nb_pion :  nombre de pions dejà trouvés par coup_obligatoire.
		 max : nombre maximum de pions pris lors d'une rafle effectuée par les pions précédents
		 n : nombre de façon de faire max prises que l'on connait déjà
		 pr,r, tableau qui contient les rafles qui font max prises que l'on connait déjà.
*/

void pion(int l, int c,int* nb_pion,int* max,int *n,int couleur,damier jeu,listeCases* pr,listeCases* r) {

int t,nb=1,nb_prises;;
Case ca;

//On tombe sur un pion de la couleur du joueur
nb_pion++;

ca.lig=l;
ca.col=c;
// On alloue de la memoire
r = (listeCases*) malloc(sizeof(listeCases));
r[0] = (listeCases) malloc(sizeof(struct element));
//Calcule le nombre de prises
nb_prises = max_pion_prises(ca,couleur,&jeu,r,&nb);

if(nb_prises == *max && nb_prises > 0) {
// On a trouvé nb autres possibilité d'effectuer max prises
	for(t=0;t<nb;t++) {
	// Pour chaque possibilité on l'ajoute a notre tableau pr
		pr[*n+t] = (listeCases) malloc(sizeof(struct element));
		pr[*n+t]->suivante = r[t]->suivante;
		pr[*n+t]->c = r[t]->c;
	}
	// Il ya maintenant n + nb possiblité de faire max prises
	*n=*n+nb;
}

if(nb_prises > *max) {
// On a trouvé np possiblités de faire plus que max prises

	// Il y a donc nb possibilités de faire max prises
	*n = nb;
	*max = nb_prises;

	for(t=0;t<nb;t++) {
	// Pour chaque possibilité on les mets dans le tableau pr
		pr[t] = (listeCases) malloc(sizeof(struct element));
		pr[t]->suivante = r[t]->suivante;
		pr[t]->c = r[t]->c;
	}

}

}


/*
	Fonction renvoyant le coup obligatoire

	param: couleur: couleur du joueur
	 	jeu: structure contenant le jeu
		pr : tableau de suites de cases contenant les divers coups possibles
		n : nombre de possibilités de prendre le max de pions
		r : varaible temp pour eviter la destruction de la mémoire quand on
		quitte la fonction

	return : -1: si libre
	          n : le nombre de prises max
*/
int coup_obligatoire(int couleur,damier jeu,listeCases* pr,listeCases* r,int* n) {

int l,c,max_pions,max=0;
int nb_pion=0; // Nombre de pions trouvés du joueurs


//Nombre de pion du joueur :  couleur
if(couleur == PION_NOIR) max_pions = jeu.nb_noir;
else max_pions = jeu.nb_blanc;




// On parcoure tout le tableau
	for(l=0;l<10;l++) {
		for(c=0;c<10;c++) {
			if(jeu.plateau[l][c] == couleur)
				pion(l,c,&nb_pion,&max,n,couleur,jeu,pr,r);
			else {
				if(jeu.plateau[l][c] == 2*couleur) {
					dame(l,c,&nb_pion,&max,n,couleur,jeu,pr,r);
				}
			}
		}
	}

return max;
}


/*
	Fonction qui dit si une prise est possible
	param:
		c,l : colonne et indice du pion que l'on test
		plateau : plateau du jeu qui contient la position des pions
		prises : tableau de cases d'arrivée en case de prise possible
	return : le nombre de possibilités de prises (taille du tableau prises)
*/
int pion_prise(int c,int l,int couleur,int plateau[10][10],Case* prises) {
int i=0;
        //On regarde dans les 4 diagonales, s'il existe un pion prenable.
	if(l-2 >=0 && c-2 >=0 && plateau[l-2][c-2] == CASE_VIDE) {
		if(plateau[l-1][c-1] == -couleur || plateau[l-1][c-1] == -couleur*2) {
			(prises+i)->lig=l-2;
			(prises+i)->col=c-2;
			i++;
		}
	}

	if(l-2>=0 && c+2<10 && plateau[l-2][c+2] == CASE_VIDE) {
		if(plateau[l-1][c+1] == -couleur || plateau[l-1][c+1] == -couleur*2) {
			(prises+i)->lig=l-2;
			(prises+i)->col=c+2;
			i++;
		}
	}

	if(l+2<10 && c-2>=0 && plateau[l+2][c-2] ==CASE_VIDE ) {
		if(plateau[l+1][c-1] == -couleur || plateau[l+1][c-1] == -couleur*2) {
			(prises+i)->lig=l+2;
			(prises+i)->col=c-2;
			i++;
		}
	}

	if(l+2 <10 && c+2 < 10 && plateau[l+2][c+2] == CASE_VIDE) {
		if(plateau[l+1][c+1] == -couleur || plateau[l+1][c+1] == -couleur*2) {
			(prises+i)->lig=l+2;
			(prises+i)->col=c+2;
			i++;
		}
	}


return i;
}


/*
	Fonction qui déplace un pion

	param: couleur: couleur du pion a déplacer
	       d : deplacement a effectuer
	       jeu : structure du jeu
*/

void deplace_pion(int couleur,deplacement d,int prise,damier* jeu) {


jeu->plateau[d.case_i.lig][d.case_i.col] = CASE_VIDE;
jeu->plateau[d.case_f.lig][d.case_f.col] = couleur;

if(prise == 1) {
	if(couleur == PION_BLANC)
		jeu->nb_noir--;
	else  jeu->nb_blanc--;
	jeu->plateau[(d.case_f.lig + d.case_i.lig)/2][(d.case_f.col + d.case_i.col)/2]=CASE_VIDE;
}

}


/*
	Fonction qui retourne le nombre de prise maximal a partir de la position c,l

	param : case_i : case a partir de laquelle ou souhaite calculer le nombre de
			prises maximale
		couleur : couleur du joueur
		jeu : structure contenant le jeu
		rafle_max : tableau de suite de cases, chaque element du tableau
		contient une suite de cases.
		n : nombre de façon differente de prendre le max de pions, correspond
			au nombre d'élément du tableau.
*/

int max_pion_prises(Case case_i, int couleur, damier* jeu, listeCases* rafle_max,int* n) {

int prises = 0; //0 si on peut pas prendre en case_i, 1 sinon
int prises_p; //Nombre de prises max en n_case(i]
int prises_max = 0; //Nombre max de prises possibles trouvées
int np; //Nb de possibilité de prendre la max de pions en n_case[i]
int nb; //Contient le nombre de possibilité de prises en case_i
//Variable d'indice, de boucle
int i,t,ind=0;

//Variable servant au calcul
Case n_case[4];
deplacement d;
damier cjeu;
listeCases* r;

if ((nb = pion_prise(case_i.col,case_i.lig,couleur,jeu->plateau,n_case))!=0) {
//Le pions situé en case_i peut prendre nb pions

//On créé une copie du jeu qui va nous permettre de simuler les coups sans affecter le damier original
	cjeu = copie_damier(jeu);

//On peut prendre un pion -> prises =1
	prises++;

//Pour chaque possibilité de prises, on calcule le nombre de prises maximales que l'on peut faire
	for(i=0;i<nb;i++) {

//On initialise le nombre de façon de faire
		np = 1;

// On alloue de la place
		r = (listeCases*) malloc(sizeof(listeCases));
		r[0] = (listeCases) malloc(sizeof(struct element));
//On cree une variable déplacement et on effectue le deplacement
		d.case_f = n_case[i];
		d.case_i = case_i;
		deplace_pion(couleur,d,1,&cjeu);
//Calcul du nombre de prises max a partir de cette position
		prises_p = max_pion_prises(n_case[i],couleur,&cjeu,r,&np);

		if(prises_p == prises_max && prises_p>0) {
// Il y a d'autre possibilité de prendre prises_max pion, mais en passant par un autre endroit
			for(t=0;t<np;t++) {
// Pour chaque nouvelle possibilité on cree une nouvelle case dans rafle_max
				rafle_max[ind] = (listeCases) malloc(sizeof(struct element));
//On lui affecte les valeurs
				rafle_max[ind]->suivante = r[t];
				rafle_max[ind]->c = case_i;
				ind++;
			}
// Correction de l'ind
			ind--;
// On ajour au nombre de possibilités les np que l'on vient de trouver
			*n=*n+np;

		}

		if(prises_p == 0 && prises_max==0) {
// On ne peut plus prendre de pion

//  On cree le dernier element de la liste
			r[0]->c = n_case[i];
			r[0]->suivante = 0;

// On créé une nouvelle case dans le tableau
			rafle_max[ind] = (listeCases) malloc(sizeof(struct element));
// On lui affecte les valeurs correpondantes
			rafle_max[ind]->suivante = r[0];
			rafle_max[ind]->c = case_i;
// L'indice augmente de 1 car on a trouvé un moyen de faire prises_max
			ind++;
			*n =ind;
		}

		if(prises_p > prises_max) {
// On a trouvé np moyen de faire plus de prises

//Il y a np moyen
			*n = np;
			prises_max = prises_p;

//On met dans le tableau tous les possibilités qu'on a trouvées
			for(ind=0;ind<np;ind++) {
				rafle_max[ind] = (listeCases) malloc(sizeof(struct element));
				rafle_max[ind]->suivante = r[ind];
				rafle_max[ind]->c = case_i;
			}

		}
	}

}
else {
//Si on ne peut pas prendre, on est en fin de liste, d'ou suivante pointe vers null
	for(t=0;t<ind;t++)
		rafle_max[t]->suivante = 0;
}
//On retourne le nombre de prises maximales
	return prises + prises_max;
}


/*
	Fonction qui execute un coup
*/

void faire_coup(listeCases pr,int couleur, damier* jeu) {

listeCases rafle;
deplacement d;
Case prise;
Case tableau[10];
int i,j,ind;
rafle = pr;

while(rafle->suivante != 0) {
// On parcoure la liste chainée, et on effectue le déplacement un à un.
	d.case_i = rafle->c;
	d.case_f = rafle->suivante->c;
	if(jeu->plateau[d.case_i.lig][d.case_i.col]==couleur)
		deplace_pion(couleur,d,1,jeu);
	else {
	//Suivant le déplacement de la dame, on peut déduire où se trouve le pion qui va être pris
		if(d.case_i.lig > d.case_f.lig) {
			prise.lig=d.case_i.lig - 1;
			i = -1;
		}
		else {
			prise.lig=d.case_i.lig + 1;
			i = 1;
		}

		if(d.case_i.col > d.case_f.col) {
			prise.col=d.case_i.col-1;
			j=-1;
		}
		else {
			prise.col=d.case_i.col + 1;
			j=1;
		}

		deplace_dame(jeu,couleur,d,1,prise);
	}
	rafle = rafle->suivante;
}
/*
	Correspond au deplacement finale de la dame apres la rafle

*/
if(jeu->plateau[d.case_f.lig][d.case_f.col] == 2*couleur) {
ind = 0;
affiche_plateau(jeu->plateau);
d.case_i = d.case_f;
tableau[0] = d.case_i;
d.case_f.lig+=i;
d.case_f.col+=j;


// On recherche toutes les cases ou la dame peut s'arreter
while(d.case_f.lig >= 0 && d.case_f.lig <10 && d.case_f.col >= 0 && d.case_f.col <10 && jeu->plateau[d.case_f.lig][d.case_f.col] == CASE_VIDE) {
ind++;
tableau[ind] = d.case_f;
// on se déplace dans la bonne direction
d.case_f.lig+=i;
d.case_f.col+=j;
//printf("%d%d\n",d.case_f.lig,d.case_f.col);
}

// On affiche la liste des possiblités et on demande a l'utilisatuer laquelle il veut effectuer.
do {
printf("Ou voulez vous que la dame arrive ?\n");
for(i=0;i<=ind;i++)
	printf("%d. %c%d ",i+1,tableau[i].col + 'a', tableau[i].lig + 1);
printf("\n");
scanf("%d",&j);
}while(j<1 || j>ind+1);

d.case_f = tableau[j-1];
deplace_dame(jeu,couleur,d,0,d.case_i);

}

}


#endif
