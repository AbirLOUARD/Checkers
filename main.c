#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"
#include "damier.h"
#include "jeu.h"
#include "cpu.h"
#include "dames.h"
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
//Tableau stockant le position des pions
damier jeu;
listeCases *rafle,*tmp;
int quitter=0,coup,n=0,ok,statut;
char r;
int reponse;

//On initialise le damier
init_damier(&jeu);

rafle = (listeCases*) malloc(sizeof(listeCases));

tmp = (listeCases*) malloc(sizeof(listeCases));
printf ("\e[?40h\e[?3h");
printf("\033[42m");
printf("************************************************\n");
printf("*                Bienvenue                     *\n");
printf("*                                              *\n");
printf("*               Jeu de Dames                   *\n");
printf("*                                              *\n");
printf("*                                              *\n");
printf("*  Auteurs : Abir Dimitri Maria                *\n");
printf("*                                              *\n");
printf("************************************************\n");
printf("\033[00m");
/*
	Saisie des joueurs
*/

joueur1 = (joueur*) malloc(sizeof(joueur));
joueur2 = (joueur*) malloc(sizeof(joueur));

joueur1->nom = malloc(20);
joueur2->nom = malloc(20);

printf("\033[45m");
printf("Entrez votre nom : \n");
printf("\033[00m");
scanf("%s",joueur1->nom);

do {
ok=1;
printf("\033[45m");
printf("Vous voulez les blancs(b) ou les noirs(n) ?\n");
printf("\033[00m");
scanf("%c",&r);
scanf("%c",&r);
if(r=='b') {
	joueur1->couleur=PION_BLANC;
	joueur2->couleur=PION_NOIR;
	joueur_c = joueur1;
}

else {
	if(r=='n') {
		joueur1->couleur=PION_NOIR;
		joueur2->couleur=PION_BLANC;
		joueur_c = joueur2;
	}

	else ok=0;
}
}while(ok==0);

do {
ok=1;
printf("\033[45m");
printf("Adversaire : Ordinateur(o) ou Humain(h) :\n");
printf("\033[00m");
scanf("%c",&r);
scanf("%c",&r);
if(r=='o') {
	joueur2->type=CPU;
	joueur2->nom = "cpu";
}
else {
	if(r=='h') {
		joueur2->type=HUMAIN;
		printf("\033[45m");
		printf("Nom de deuxième joueur:\n");
		printf("\033[00m");
		scanf("%s",joueur2->nom);
	}
	else ok=0;
}
 do
 {
    printf("\033[45m");
    printf("veillez selectionnez le niveau de difficulte svp\n");
    printf("\033[00m");
    printf("1: niveau easy\n");
    printf("2: niveau hard\n");
    scanf("%d",&nivau);
 }while(nivau != 1 && nivau!=2);

}while(ok==0);

do
 {
    printf("\033[45m");
    printf("voulez-vous enregistrer les details de la partie svp\n");
    printf("\033[00m");
    printf("1: OUI\n");
    printf("0: NON\n");
    scanf("%d",&reponse);
    if(reponse==1)
    {
        details_joueurs();
        printf("svp entrer le nom du fichier suivi de .txt \n:");
        scanf("%s",file_sav);
    }

 }while(reponse != 1 && reponse!=0);

/*
	Debut du jeu
*/
clock_t t;
t=clock();
do {


coup = coup_obligatoire(joueur_c->couleur,jeu,rafle,tmp,&n);

if(joueur_c->type==HUMAIN) {
	affiche_damier(jeu.plateau);

if(joueur_c->couleur == PION_NOIR)
{

printf("\nC'est a %s de jouer avec les noirs (%d pions / %d)\n",joueur_c->nom,jeu.nb_noir,jeu.nb_blanc);

}
else
{

printf("\nC'est a %s de jouer avec les blancs (%d pions / %d)\n",joueur_c->nom,jeu.nb_blanc,jeu.nb_noir);

}
    printf("\033[44m");
	printf(" Nombre de prises maximum : %d\n",coup);
	printf("\033[00m");

	if(tour_joueur(&jeu,&joueur_c->couleur,n,rafle,coup) == -1)
    {
       quitter = 1;
    }

}
else {
	if(jouer_cpu(&jeu,joueur_c->couleur,coup,rafle)==-1) {
		printf("L'ordinateur abandonne, vous avez gagner !!!\n");
		quitter=1;
	}
}

faire_dames(&jeu,joueur_c->couleur);

//On change de joueur
	if(joueur_c == joueur1)
		joueur_c = joueur2;

	else joueur_c = joueur1;

} while(quitter==0 && (statut = jeu_fini(&jeu,joueur_c->couleur))==0);
affiche_damier(jeu.plateau);

if(statut == PION_NOIR)
	printf("Les blancs ont gagné\n");
else { if(statut == PION_BLANC)
		printf("Les noirs ont gagné\n");
	else printf("A bientot !!!\n");
}
t=clock()-t;
double time_taken = ((double)t)/ CLOCKS_PER_SEC;
printf("%f",time_taken);
return 1;
}
