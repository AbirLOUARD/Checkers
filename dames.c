 #ifndef DAMES_C
 #define DAMES_C

/*
       Ce module est consacré aux fonctions liées au déplacement des dames, mais aussi à la recherche
       de la rafle maximale pour une dame.

*/

#include "dames.h"

/*
       Fonction appelée à chaque fin de tour qui promoue un pion en dame
       si celui-ci se trouve sur la ligne de fond adverse.

*/
void faire_dames(damier* jeu,int couleur) {
int i,j;


if(couleur==PION_NOIR) {
// On verifie la ligne de fond des blancs
	i=9;
	j=0;
}
else {
//On verifie la ligne de fond des noirs
	i=0;
	j=1;
}

 for(j;j<10;j+=2) {
 	if(jeu->plateau[i][j] == couleur)
//      Si il ya un pion on le transforme en dame (*2)
		jeu->plateau[i][j] = 2*couleur;
 }


 }

/*
	Fonction qui teste si le deplacement d'une dame est valide
	return 1 si ok
	       -1 sinon
*/

int test_deplace_dame(damier* jeu, int couleur,deplacement d) {
int i=d.case_i.lig,j=d.case_i.col;

if(jeu->plateau[i][j] != couleur*2) {
	printf("%c%d n'est pas une dame\n",j+'a',i+1);
	return -1;
}

while(i!=d.case_f.lig || j!= d.case_f.col) {
	if(d.case_f.lig>d.case_i.lig)
		i++;
	else
		i--;

	if(d.case_f.col>d.case_i.col)
		j++;
	else
		j--;

	if(jeu->plateau[i][j] != CASE_VIDE) {
		printf("%c%d n'est pas vide\n",j+'a',i+1);
		return -1;
	}
}
return 1;
}

/*
        Fonction qui regarde combien de pions la dames en ca peut prendre, et les stockes
	dans les tableaux de cases : d et a

	return : le nombre de pions prenables (max 4)
	param : ca : case ou se trouve la dame
	        d tableau de cases qui correspond aux directions, ie. la diagonale ou se trouve le pion
		             eg. pion prenable dans la diagonale haut droite :
			               case[i] contient la case de pion
				       d[i] contient (-1,+1)

		a tableau de case d'arrivée, ie. la case qui se trouve juste avant le pion a prendre
*/

int prise_possible(damier* jeu,int couleur,Case ca,Case* d,Case* a) {

int i,j,n=0,stop;

//Colonne +1, ligne +1
i=ca.lig+1;
j=ca.col+1;
stop=0;

while(i<10 && j<10 && stop==0) {
if(jeu->plateau[i][j] == -couleur || jeu->plateau[i][j] == -couleur*2) {
	stop=1;
	if(jeu->plateau[i+1][j+1] == CASE_VIDE && i+1 <10 && j+1 <10) {
		d[n].lig = 1;
		d[n].col = 1;
		a[n].lig = i-1;
		a[n].col = j-1;
		n++;
	}
}
else {
if(jeu->plateau[i][j] != CASE_VIDE)
	stop = 1;
}
i++;j++;
}


//Colonne +1, ligne -1
i=ca.lig-1;
j=ca.col+1;
stop=0;

while(i>=0 && j<10 && stop==0) {

if(jeu->plateau[i][j] == -couleur || jeu->plateau[i][j] == -couleur*2) {
	stop=1;
	if(i-1>=0 && j+1<10 && jeu->plateau[i-1][j+1] == CASE_VIDE) {
		d[n].lig = -1;
		d[n].col = 1;
		a[n].lig = i+1;
		a[n].col = j-1;
		n++;
	}
}
else {
if(jeu->plateau[i][j] != CASE_VIDE)
	stop = 1;
}
i--;j++;
}

//Colonne -1 Ligne -1

i=ca.lig-1;
j=ca.col-1;
stop=0;

while(i>=0 && j>=0 && stop==0) {
if(jeu->plateau[i][j] == -couleur || jeu->plateau[i][j] == -couleur*2) {
	stop=1;
	if(jeu->plateau[i-1][j-1] == CASE_VIDE && i-1>=0 && j-1>=0) {
		d[n].lig = -1;
		d[n].col = -1;
		a[n].lig = i+1;
		a[n].col = j+1;
		n++;
	}
}
else {
if(jeu->plateau[i][j] != CASE_VIDE)
	stop = 1;
}
i--;j--;
}


//Colonne -1 ligne +1
i=ca.lig+1;
j=ca.col-1;
stop=0;

while(i<10 && j>=0 && stop==0) {
if(jeu->plateau[i][j] == -couleur || jeu->plateau[i][j] == -couleur*2) {
	stop=1;
	if(jeu->plateau[i+1][j-1] == CASE_VIDE && i+1<10 && j-1>=0) {
		d[n].lig = 1;
		d[n].col = -1;
		a[n].lig = i-1;
		a[n].col = j+1;
		n++;
	}
}
else {
if(jeu->plateau[i][j] != CASE_VIDE)
	stop = 1;
}
i++;j--;
}

return n;

}



/*
	Deplace une dame suivant le deplacement d,
	prise vaut 1 si il y a une prise lors du déplacement.
	Dans ce cas, prise correspond a cette case
*/
void deplace_dame(damier* jeu, int couleur,deplacement d, int p, Case prise) {

	//Lors d'un cup obligatoire, bug :case_i = case_f
	if(d.case_i.lig == d.case_f.lig && d.case_i.col == d.case_f.col)
		return;
	jeu->plateau[d.case_i.lig][d.case_i.col] = CASE_VIDE;
	jeu->plateau[d.case_f.lig][d.case_f.col] = 2*couleur;

	if(p==1 && (jeu->plateau[prise.lig][prise.col]==-couleur || jeu->plateau[prise.lig][prise.col]==-couleur*2)) {
		jeu->plateau[prise.lig][prise.col] = CASE_VIDE;

		if(couleur == PION_BLANC)
			jeu->nb_noir = jeu->nb_noir -1;
		else jeu->nb_blanc = jeu->nb_blanc - 1;
	}
}

/*
	Fonction qui renvoie les possiblité de prises
	return : le nombre de prises possibles.
	param :
	    Entrée :
	       c,l : position de la dame
	       ic,il : direction dans laquelle la dame peut se deplacer.
	       plateau[10][10] : tableau du jeu
	       couleur : couleur des pions du joueur
	    Sortie :
	       n_case : tableau de cases contenant les positions de la dames ou elle peut prendre un
	       pion adverse.
	       direction : tableau de cases contenant les directions de prises, elles correspondent au
	       cases de n_case

                   |___|_X_| 1
                 __|___|___| 2   n_case[1] = (b,2) et direction[1] = (+1,+1)
	       [O] |   |   | 3
	         a   b   c


*/
int dame_prise(int c,int l,int ic,int il,int couleur,int plateau[10][10],Case* n_case, Case* direction) {

// Initialisation de i et j.
// En effet dans notre algorithme de recherche de rafle maximale, dame_prise est appelée avec la case (c,l)
// précédant un pion pouvant être pris dans la direction (ic,il), Par conséquent on effectue la recherche a
// partir de la case juste après ce pion.

int i=l+2*il,j=c+2*ic,n=0;

while(i>=0 && i<10 && j>=0 && j<10) {
//On parcoure toute la diagonle dans le sens ic,il a partir de c,l
	if(plateau[i][j] == CASE_VIDE) {
	// Si la nouvelle case est vide on teste s'il existe un pion prenable dans chacune
	// des trois directions possibles

	if(plateau[i+il][j+ic] == -couleur || plateau[i+il][j+ic] == -couleur*2) {
	//Si la case suivante est occupée par un pion ou une dame de la couleur adverse.
		if(plateau[i+2*il][j+2*ic]==CASE_VIDE||plateau[i+2*il][j+2*ic]==CASE_VIDE) {
       // On vérifie que la case encore apres est vide, et donc que la prise est possible.
			if(i+2*il >= 0 && i+2*il <10  && j+2*ic <10 && j+2*ic >=0) {
			n_case[n].lig = i;
			n_case[n].col = j;
			direction[n].lig = il;
			direction[n].col = ic;
			n++;
			}
		}
	}

	if(plateau[i+il][j-ic] == -couleur || plateau[i+il][j-ic] ==-2*couleur) {
		if(plateau[i+2*il][j-2*ic]==CASE_VIDE||plateau[i+2*il][j-2*ic]==CASE_VIDE) {
			if(i+2*il >= 0 && i+2*il <10  && j+2*ic <10 && j+2*ic >=0) {
			n_case[n].lig = i;
			n_case[n].col = j;
			direction[n].lig = il;
			direction[n].col = -ic;
			n++;
			}
		}
	}

	if(plateau[i-il][j+ic] == -couleur || plateau[i-il][j+ic]==-2*couleur) {
		if(plateau[i-2*il][j+2*ic]==CASE_VIDE||plateau[i-2*il][j+2*ic]==CASE_VIDE) {
			if(i+2*il >= 0 && i+2*il <10  && j+2*ic <10 && j+2*ic >=0) {
			n_case[n].lig = i;
			n_case[n].col = j;
			direction[n].lig = -il;
			direction[n].col = ic;
			n++;
			}
		}
	}

	}
// 	Si la case n'est pas vide, ça veut dire que la dame est bloquée par un pion
	else return n;
// 	On increment nos compteurs
	i+=il;
	j+=ic;
}
return n;
}


/*
	Fonction qui renvoie une copie de la structure jeu
*/

damier copie_damier(damier* jeu) {

damier cjeu;
int i,j;

cjeu.nb_blanc = jeu->nb_blanc;
cjeu.nb_noir = jeu->nb_noir;
for(i=0;i<10;i++) {
	for(j=0;j<10;j++)
		cjeu.plateau[i][j] = jeu->plateau[i][j];
}
return cjeu;
}

/*
	Fonction qui retourne le nombre de prises maximal a partir de la position c,l (dame)

	param :
	     entrée :
		case_i : case a partir de laquelle on souhaite calculer le nombre de
			prises maximale
		couleur : couleur du joueur
		jeu : structure contenant le jeu
             sortie :
		rafle_max : tableau de suite de cases, chaque element du tableau,
		contient une suite de cases. (tableau de liste chainée)
		n : nombre de façons differentes de prendre le max de pions, correspond
			au nombre d'éléments du tableau.
*/

int max_dame_prises(Case case_i, Case sens, int couleur, damier* jeu, listeCases* rafle_max,int* n) {

int prises = 0; //0 si on peut pas prendre en case_i, 1 sinon
int prises_p; //Nombre de prises max en n_case(i]
int prises_max = 0; //Nombre max de prises possibles trouvé
int np; //Nb de possibilités de prendre le max de pions en n_case[i]
int nb; //Contient le nombre de possibilités de prises en case_i
//Variable d'indice, de boucle
int i,t,ind=0;

//Variable servant au cacul
Case direction[10],n_case[10],p;
deplacement d;
damier cjeu;
listeCases *r,tmp;

if ((nb = dame_prise(case_i.col,case_i.lig,sens.col,sens.lig,couleur,jeu->plateau,n_case,direction))!=0) {
//Le pions situé en case_i peut prendre nb pions

//On crée une copie du jeu qui va nous permettre de simuler les coups sans affecter le damier original
	cjeu = copie_damier(jeu);

//On peut prendre un pion -> prises =1
	prises++;

//Pour chaque possibilité de prises, on calcule le nombre de prises maximales que l'on peut faire
	for(i=0;i<nb;i++) {

//On initialise le nombre de façons de faire
		np = 1;

// On alloue de la place
		r = (listeCases*) malloc(sizeof(listeCases));
		r[0] = (listeCases) malloc(sizeof(struct element));
//On cree une variable déplacement et on effectue le deplacement
		d.case_f = n_case[i];
		d.case_i = case_i;
		p.lig = case_i.lig + sens.lig;
		p.col = case_i.col + sens.col;
		deplace_dame(&cjeu,couleur,d,1,p);
//Calcul du nombre de prises max a partir de cette position
		prises_p = max_dame_prises(n_case[i],direction[i],couleur,&cjeu,r,&np);

		if(prises_p == prises_max && prises_p>0) {
// Il y a d'autres possibilités de prendre prises_max pion, mais en passant par un autre endroit
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
// On ajoute au nombre de possibilités les np que l'on vient de trouver
			*n=*n+np;

		}

		if(prises_p == 0 && prises_max==0) {
// On ne peut plus prendre de pion

//  On cree le dernier element de la liste
			tmp = (listeCases) malloc(sizeof(listeCases));
			tmp->c = n_case[i];
			tmp->suivante = r[0];

// On crée une nouvelle case dans le tableau
			rafle_max[ind] = (listeCases) malloc(sizeof(struct element));
// On lui affecte les valeurs correpondantes
			rafle_max[ind]->suivante = tmp;
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
	tmp = (listeCases) malloc(sizeof(struct element));
	tmp->suivante = 0;
	tmp->c.lig = case_i.lig	+ 2*sens.lig;
	tmp->c.col = case_i.col + 2*sens.col;
	rafle_max[0]->c = case_i;
	rafle_max[0]->suivante = tmp;

}

//On retourne le nombre de prises maximales
	return prises + prises_max;
}


/*
          Fonction qui caclcule la rafle maximale pouvant être effectuée par la dame située en c,l
	  Cette fonction est appelée dans la fonction coup obligatoire qui parcourt tous le damier
	  à la recherche de tous les pions du joueur.
	  param :
	     Entrée:
		 c,l : case ou se trouve la dame
		 jeu : structure du jeu
	     Entrée / Sortie :
		 nb_pion :  nombre de pion dejà trouvé par coup_obligatoire.
		 max : nombre maximum de pions pris lors d'une rafle effectuée par les pions précédants
		 n : nombre de façon de faire max prises que l'on connait déjà
		 pr,r, tableau qui contient les rafles qui font max prises que l'on connait déjà.

*/
void dame(int l, int c,int* nb_pion,int* max,int *n,int couleur,damier jeu,listeCases* pr,listeCases* r) {

int t,nb=1,nb_prises,i,pp;
Case ca,d[4],a[4];
deplacement depla;
damier cjeu;

listeCases* tmp;
tmp = (listeCases*) malloc(sizeof(listeCases*));

//On tombe sur un pion de la couleur du joueur
nb_pion++;

ca.lig=l;
ca.col=c;
// On alloue de la memoire
r = (listeCases*) malloc(sizeof(listeCases));
r[0] = (listeCases) malloc(sizeof(struct element));

if( (pp = prise_possible(&jeu,couleur,ca,d,a)) != 0) {
printf("DAME prise posible : %d\n",pp);
for(i=0;i<pp;i++) {
	//Calcule le nombre de prises
	cjeu = copie_damier(&jeu);
	depla.case_i = ca;
	depla.case_f = a[i];
	deplace_dame(&cjeu,couleur,depla,0,ca);
	nb_prises = max_dame_prises(a[i],d[i],couleur,&cjeu,r,&nb);
	nb_prises++;
	if(nb_prises == *max && nb_prises > 0) {
	// On a trouvé nb autres possibilité d'effectuer max prises
		for(t=0;t<nb;t++) {
		// Pour chaque possibilité on l'ajoute a notre tableau pr
			pr[*n+t] = (listeCases) malloc(sizeof(struct element));
			tmp[*n+t] = (listeCases) malloc(sizeof(listeCases));
			tmp[*n+t]->suivante = r[t]->suivante;
			tmp[*n+t]->c = r[t]->c;
			pr[*n+t]->suivante = tmp[*n+t];
			pr[*n+t]->c = ca;
		}
		// Il ya maintenant n + nb possiblité de faire max prises
		*n=*n+nb;
	}

	if(nb_prises > *max) {
	// On a trouve np possiblité de faire plus que max prises

	// Il y a donc nb possibilité de faire max prises
		*n = nb;
		*max = nb_prises;

		for(t=0;t<nb;t++) {
		// Pour chaque possibilité on les mets dans le tableau pr
			pr[t] = (listeCases) malloc(sizeof(struct element));
			tmp[0] = (listeCases) malloc(sizeof(listeCases));
			tmp[0]->suivante = r[t]->suivante;
			tmp[0]->c = r[t]->c;
			pr[t]->suivante = tmp[0];
			pr[t]->c = ca;

		}
	}
}
}
}

 #endif
