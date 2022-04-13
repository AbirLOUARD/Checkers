#ifndef DAMIER_C
#define DAMIER_C


#include "damier.h"

/*
    Fonction qui initialise le damier
*/

void init_damier(damier* jeu) {
jeu->nb_blanc = 20;
jeu->nb_noir = 20;
int i,j;
for(i=0;i<10;i++)
    for(j=0;j<10;j++)
        jeu->plateau[i][j] = 0;
//On remplit la partie haute du damier par des pions noirs
for(i=0;i<4;i++) {
//Si i est pair, la premiere case doit etre noir (active)
      if(i%2 == 0) j=1;
      else j=0;

      for(j;j<10;j+=2)
           jeu->plateau[i][j] = PION_NOIR;


}

//On remplie la partie basse du damier par des pions blancs
for(i=6;i<10;i++) {
//Si i est pair, la premiere case doit etre noir (active)
      if(i%2 == 0) j=1;
      else j=0;

      for(j;j<10;j+=2)
           jeu->plateau[i][j] = PION_BLANC;

}
}

/*
	Fonction qui teste si le deplacement est autorisé
	retourne -1 en cas d'erreur
	1 en cas de prise
	0 en cas de bon deplacement
*/

int test_deplacement(int couleur,deplacement d,int damier[10][10]) {

//Case occupée
if(damier[d.case_f.lig][d.case_f.col] != CASE_VIDE)
{

       return -1;
}


//Mauvaise Ligne
if(d.case_f.lig != d.case_i.lig - couleur)
 {

        return -1;
}


//Mauvaise colonne
if(d.case_f.col != (d.case_i.col+1) &&  d.case_f.col != (d.case_i.col-1) ) {

        return -1;
}

return 0;

}

/*
	Fonction qui teste si une case est dans le damier
*/
int test_case(Case c) {
	if(c.lig<1 || c.lig > 10 || c.col > 10 || c.col < 0)
		return -1;
	return 0;
}


/*
	Fonction qui lit une action (déplacement)

	retourne :
		-1 en cas de mauvais déplacment
		0 en cas de bon déplacement
		2 si l'utilisateur veut réafficher le plateau
		3 si l'utilisateur veut quitter
		4 si l'utilisateur charge un nouveau fichier
		5 si l'utilisateur sauvegarde la partie
		6 si l'utilisateur veut voir l'aide
		7 si l'utilisateur veut revisualiser une partie

*/
int lecture_deplacement(deplacement* d,damier* jeu,int couleur) {

char start[20],fin[5];

printf("Entrez la colonne puis la ligne du pion a deplacer:\n");
fflush(stdin);
scanf("%s",start);
//On verifie que l'utilisateur n'a pas rentré une commande
if(strcmp(start,"aide") == 0)
    {
        printf("\033[32m");
        printf("  -> votre choix est: Afficher les options du jeu\n\n");
        printf("\033[00m");
        return affiche_aide();
    }
if(strcmp(start,"quitter") == 0)
  {
        printf("\033[32m");
        printf("  -> votre choix est: Quitter le jeu\n\n");
        printf("\033[00m");
        return affiche_quitter();
    }
if(strcmp(start,"charger") == 0)
    {
        printf("\033[32m");
        printf("  -> votre choix est: Charger une partie\n\n");
        printf("\033[00m");
        return affiche_load(jeu);
    }

if(strcmp(start,"revisualiser") == 0)
    {
        printf("\033[32m");
        printf("  -> votre choix est: Revisualiser une partie \n\n");
        printf("\033[00m");
        affiche_revisualiser(jeu);
        affiche_aide();
    }

if(strcmp(start,"sauver") == 0)
    {
        printf("\033[32m");
        printf("  -> votre choix est: Sauvegarder la partie en cours\n\n");
        printf("\033[00m");
        return affiche_sauver(jeu,couleur);
    }

if(strcmp(start,"statistique") == 0)
    {
        printf("\033[32m");
        printf("  -> votre choix est: Afficher les stats des parties terminees\n\n");
        printf("\033[00m");
        affiche_stat();
        return affiche_aide();
    }

if(strcmp(start,"damier") == 0)
{
        printf("\033[32m");
        printf("  -> votre choix est: Redemarrer la partie\n\n");
        printf("\033[00m");
        return affiche_plateau(jeu->plateau);
    }
scanf("%s",fin);

if('a' > start[0] || start[0] > 'k' || 'a' > fin[0] || fin[0] > 'k')
	return -1;

if('1' > start[1] || start[1] > '9' || '1' > fin[1] || fin[1] > '9')
	return -1;

d->case_i.col = start[0] - 'a';
d->case_i.lig = start[1] - '1';

d->case_f.col = fin[0] - 'a';
d->case_f.lig = fin[1] - '1';


//Gestion du probleme dans la 10eme ligne
if(start[1] == '1') {
	if(start[2] == '0')
		d->case_i.lig = 9;
}

if(fin[1] == '1') {
	if(fin[2] == '0')
		d->case_f.lig = 9;
}
return 0;
}

/*
	Fonction qui gere le tour d'un joueur

	Entrée :
		couleur : indique la couleur des pions du joueur
		jeu : contient le damier, ainsi que le nombre de pions de chacun des joueurs

	Retourne :
		-1 si on quitte
		1 si tout s'est bien passé
		2 si on a charge un fichier
*/
int selec_pion(int couleur,damier* jeu) {

int ok=0,dame;
int prise;

deplacement d;

do {
dame=0;
//  On lit l'entrée de l'utilisateur.
	switch(lecture_deplacement(&d,jeu,couleur)) {
	//Suivant ce qu'il fait :
//             Erreur de déplacement, mauvaise syntaxe.
		case -1:
			printf("Erreur de deplacement\n");
			break;
//              Bonne syntaxe du déplacement, on verifie qu'elle est correcte
		case 0:
		        // Cas du pion
			if(jeu->plateau[d.case_i.lig][d.case_i.col] == couleur) {
				if((prise = test_deplacement(couleur,d,jeu->plateau)) == -1) {
					printf("Impossible de deplacer le pion %c,%d en %c,%d\n",d.case_i.col+'a',d.case_i.lig+1,d.case_f.col+'a',d.case_f.lig+1);
				}
				else {
					ok = 1;
					sauver_temps_reel(jeu,couleur);
				}
			}
			// Cas de la dame
			if(jeu->plateau[d.case_i.lig][d.case_i.col] == 2*couleur) {
				if((prise = test_deplace_dame(jeu,couleur,d)) == -1)
					printf("Impossible de deplacer la dame !!!\n");
				else {
					ok = 1;
					dame=1;
					sauver_temps_reel(jeu,couleur);
				}
			}
			break;
		// l'utilisateur veut quitter
		case 3:
			return -1;
			break;
		// l'utilisateur charge un nouveau jeu
		case 4:
			return 2;
			break;
		//Dans tous les autres cas, on lui redonne la main.
		default:
			break;
	}

} while(ok == 0);

//La variable dame est a 1 si on déplace une dame
if(dame==1)
	deplace_dame(jeu,couleur,d,0,d.case_i);
else deplace_pion(couleur,d,prise,jeu);


return 1;

}


/*
	Fonction qui affiche la liste des cases lors d'un coup obligatoire
*/
void affiche_rafle(listeCases rafle) {
listeCases pr;

pr = rafle;

while(pr!=0) {
	printf("%c,%d ->",pr->c.col + 'a',pr->c.lig+1);
	pr=pr->suivante;
}
printf("\n");

}


/*
	Fonction qui propose le choix d'un coup obligatoire

	param :
	      listeCases : liste des rafles possibles.
	      n : nombre de coup possible, taille du tableau listeCases.
*/


void affiche_choixcoup(listeCases* rafle, int n, int couleur, damier* jeu) {
int ok=0,i;

do {
        //On vide le buffer
	fflush(stdin);
	printf("Plusieurs coups sont possibles %d:\n",n);
	if(nivau==1)
	{
	for(i=0;i<n;i++) {
        printf("%d : ",i+1);
		affiche_rafle(rafle[i]);
        }
	}
	//Si la valeur entrée par l'utilisateur est correcte on fait le déplacement
	if(scanf("%d",&i) ==1 && i>0 && i<=n) {
		faire_coup(rafle[i-1],couleur,jeu);
		ok = 1;
	}
}while(ok == 0);

}


/*
       Fonction gérant le tour d'un joueur
*/

int tour_joueur(damier* jeu,int* couleur,int n,listeCases* rafle,int coup) {
if(coup > 0 )
	affiche_choixcoup(rafle,n,*couleur,jeu);

else {
	if(selec_pion(*couleur,jeu)==-1)
		return -1;
}
return 0;

}
#endif
