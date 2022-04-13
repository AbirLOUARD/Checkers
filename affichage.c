#ifndef AFFICHAGE_C
#define AFFICHAGE_C

#include "affichage.h"

/*
   Fonction qui affiche la ligne i du damier

*/

void affiche_ligne(int i,int damier[10][10]) {
int j;

printf(" %2d ",i+1);
for(j=0;j<10;j++) {
	switch(damier[i][j]) {
		case PION_BLANC:
		printf("\033[37m");
			printf("|  B  ");
			printf("\033[00m");
			break;
		case PION_NOIR:
		printf("\033[30m");
			printf("|  N  ");
			printf("\033[00m");
			break;
		case DAME_NOIR:
		printf("\033[30m");
			printf("| [N] ");
			printf("\033[00m");
			break;
		case DAME_BLANC:
		printf("\033[37m");
			printf("| [B] ");
			printf("\033[00m");
			break;
		default:
			printf("|     ");
			break;
      }
}
printf("| %2d\n",i+1);
printf("    |-----------------------------------------------------------|\n");


}

/*
	Fonction qui affiche le damier en totalité
*/

void affiche_damier(int damier[10][10]) {
int i;
printf("       a     b     c     d     e     f     g     h     i     j  \n");
printf("    |-----------------------------------------------------------|\n");
for(i=0;i<10;i++)
     affiche_ligne(i,damier);

printf("       a     b     c     d     e     f     g     h     i     j  \n");


}

/* ********************************************************************************* */
/*                                                                                   */
/*                        Fonctions gérant les commandes du jeu                      */
/*                                                                                   */
/* ********************************************************************************* */

/*
	Fonction qui affiche les differentes options
*/

int affiche_aide() {
printf("\033[32m");
printf("Liste des commandes :\n");
printf("\033[00m");
printf("\ncharger : Charge une partie enregistre\n\n");
printf("damier : affiche a nouveau le plateau\n\n");
printf("quitter : Quitter la partie\n\n");
printf("sauver : Sauve la partie\n\n");
printf("revisualiser : revisualiser une partie \n\n");
printf("statistique : afficher les statistiques des partie\n\n");
printf("Un deplacement doit etre de la forme : [colonne][ligne] [colonne][ligne]\n,ou colonne appartient a [a-h] et ligne a [1-10]");
printf("\n\n");

return 6;
}


//Fonction appelée lorsque le joueur décide de quitter le jeu.
int affiche_quitter() {
printf("A bientot\n");
return 3;
}


/*
	Charge une partie à partir d'un fichier
*/

int affiche_load(damier* jeu) {
char file[50];
int i,j,couleur;
 DIR *rep = opendir ("." );
 char *verif, *verif2;

   if (rep != NULL)
   {
      struct dirent *lecture;

      while ((lecture = readdir (rep)) != NULL)
      {
         struct stat st;

         stat (lecture->d_name, &st);
         {
             //Modified time
            time_t t = st.st_mtime;
            struct tm tm = *localtime (&t);
            char s[32];
            strftime (s, sizeof s, "%d/%m/%Y %H:%M:%S", &tm);
            verif = strstr (lecture->d_name, ".txt");
            verif2 = strstr (lecture->d_name, ".TXT");
            if (verif != NULL || verif2 != NULL)
            {
            printf ("%-14s %s\n", lecture->d_name, s);

         }
      }
      }
      closedir (rep), rep = NULL;
   }



 FILE *pFile;

 printf("Nom du fichier :");
 scanf("%s",file);

 pFile = fopen(file,"r");

if(pFile!=NULL) {

	for(i=0;i<10;i++) {
		for(j=0;j<10;j++)
			fscanf(pFile,"%d",&jeu->plateau[i][j]);
	}
	fscanf(pFile,"\n%d %d",&(jeu->nb_blanc),&(jeu->nb_noir));
	fscanf(pFile,"\n%d",&couleur);

	//joueur 1
	joueur2->nom = (char*) malloc(20);
	joueur1->nom = (char*) malloc(20);
	fscanf(pFile,"%s ",joueur1->nom);
	fscanf(pFile,"%d ",&(joueur1->type));
	fscanf(pFile,"%d\n",&(joueur1->couleur));
	//joueur2
	fscanf(pFile,"%s ",joueur2->nom);
	fscanf(pFile,"%d ",&(joueur2->type));
	fscanf(pFile,"%d\n",&(joueur2->couleur));
	if(joueur1->couleur == couleur)
		joueur_c = joueur1;
	else joueur_c = joueur2;

fclose(pFile);
}
else printf("Impossible de charger le fichier : %s\n",file);
return 4;
}

/*
	Sauvegarde dans un fichier la partie
*/

int affiche_sauver(damier* jeu,int couleur) {
char file[50];
 int i,j;
 DIR *rep = opendir ("." );
 char *verif, *verif2;

   if (rep != NULL)
   {
      struct dirent *lecture;

      while ((lecture = readdir (rep)) != NULL)
      {
         struct stat st;

         stat (lecture->d_name, &st);
         {
             //Modified time
            time_t t = st.st_mtime;
            struct tm tm = *localtime (&t);
            char s[32];
            strftime (s, sizeof s, "%d/%m/%Y %H:%M:%S", &tm);
            verif = strstr (lecture->d_name, ".txt");
            verif2 = strstr (lecture->d_name, ".TXT");
            if (verif != NULL || verif2 != NULL)
            {
            printf ("%-14s %s\n", lecture->d_name, s);

         }
      }
      }
      closedir (rep), rep = NULL;
   }


FILE *pFile;

printf("Nom du fichier :");
scanf("%s",file);

pFile = fopen(file,"w");

if(pFile!=NULL) {

	for(i=0;i<10;i++) {
		for(j=0;j<10;j++)
			fprintf(pFile,"%d ",jeu->plateau[i][j]);
		fprintf(pFile,"\n");
	}

	fprintf(pFile,"\n%d %d",jeu->nb_blanc,jeu->nb_noir);
	fprintf(pFile,"\n%d",-couleur);

	//joueur 1
	fprintf(pFile,"\n%s",joueur1->nom);
	fprintf(pFile," %d",joueur1->type);
	fprintf(pFile," %d\n",joueur1->couleur);
	//joueur2
	fprintf(pFile,"%s",joueur2->nom);
	fprintf(pFile," %d",joueur2->type);
	fprintf(pFile," %d\n",joueur2->couleur);

fclose(pFile);
}
else printf("Impossible de creer le fichier : %s\n",file);

return 5;
}

/* revisualiser une partie sauver temps reel*/
int affiche_revisualiser(damier* jeu) {
char file[50];
int k=0, pos=0,fin=0,couleur,i,j;
 DIR *rep = opendir ("." );
 char *verif, *verif2;

   if (rep != NULL)
   {
      struct dirent *lecture;

      while ((lecture = readdir (rep)) != NULL)
      {
         struct stat st;

         stat (lecture->d_name, &st);
         {
             //Modified time
            time_t t = st.st_mtime;
            struct tm tm = *localtime (&t);
            char s[32];
            strftime (s, sizeof s, "%d/%m/%Y %H:%M:%S", &tm);
            verif = strstr (lecture->d_name, ".txt");
            verif2 = strstr (lecture->d_name, ".TXT");
            if (verif != NULL || verif2 != NULL)
            {
            printf ("%-14s %s\n", lecture->d_name, s);

         }
      }
      }
      closedir (rep), rep = NULL;
   }




 FILE *pFile;
 printf("svp entrer le nom de la partie à revisualiser\n");
 printf("Nom du fichier :");
 scanf("%s",file);

 pFile = fopen(file,"rb");

if(pFile!=NULL) {
    fseek(pFile, 0, SEEK_END);
    fin = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);
    while (pos<(fin))
    {
    k=k+1;
    printf("ETAPE NUMERO %d\n",k);

	for(i=0;i<10;i++) {
		for(j=0;j<10;j++)
			fscanf(pFile,"%d",&jeu->plateau[i][j]);
	}
	affiche_plateau(jeu->plateau);

	fscanf(pFile,"\n%d %d",&(jeu->nb_blanc),&(jeu->nb_noir));
	fscanf(pFile,"\n%d",&couleur);

	//joueur 1
	joueur2->nom = (char*) malloc(20);
	joueur1->nom = (char*) malloc(20);
	fscanf(pFile,"%s ",joueur1->nom);
	fscanf(pFile,"%d ",&(joueur1->type));
	fscanf(pFile,"%d\n",&(joueur1->couleur));
	//joueur2
	fscanf(pFile,"%s ",joueur2->nom);
	fscanf(pFile,"%d ",&(joueur2->type));
	fscanf(pFile,"%d\n",&(joueur2->couleur));
	if(joueur1->couleur == couleur)
		joueur_c = joueur1;
	else joueur_c = joueur2;

    sleep(2);
	pos=ftell(pFile);
	fseek(pFile, 0, SEEK_CUR);

    }

fclose(pFile);
}
else printf("Impossible de charger le fichier : %s\n",file);
return 4;

}
/*sauver chaque deplacement des pions*/

void sauver_temps_reel(damier* jeu,int couleur) {
FILE *pFile;
int i,j;
 pFile = fopen(file_sav, "a");

if(pFile!=NULL) {

	for(i=0;i<10;i++) {
		for(j=0;j<10;j++)
			fprintf(pFile,"%d ",jeu->plateau[i][j]);
		fprintf(pFile,"\n");
	}

	fprintf(pFile,"\n%d %d",jeu->nb_blanc,jeu->nb_noir);
	fprintf(pFile,"\n%d",-couleur);

	//joueur 1
	fprintf(pFile,"\n%s",joueur1->nom);
	fprintf(pFile," %d",joueur1->type);
	fprintf(pFile," %d\n",joueur1->couleur);
	//joueur2
	fprintf(pFile,"%s",joueur2->nom);
	fprintf(pFile," %d",joueur2->type);
	fprintf(pFile," %d\n",joueur2->couleur);

fclose(pFile);
}
else printf("Impossible de charger le fichier : %s\n",file_sav);

}
/*
	Affiche la plateau
*/
int affiche_plateau(int plateau[10][10]) {

	affiche_damier(plateau);
	return 2;
}
void details_joueurs()
{
    Victoire v;
    FILE* sauv_det = NULL;
int i,j;
 sauv_det = fopen("sauv_det.txt", "a+");

if(sauv_det!=NULL) {

	//joueur 1
	fprintf(sauv_det,"\n%s",joueur1->nom);
	fprintf(sauv_det," %d",joueur1->type);
	fprintf(sauv_det," %d\n",joueur1->couleur);
	//joueur2
	fprintf(sauv_det,"%s",joueur2->nom);
	fprintf(sauv_det," %d",joueur2->type);
	fprintf(sauv_det," %d\n",joueur2->couleur);
	//difficulté
	if(nivau==1)
	{
       fprintf(sauv_det,"easy\n");
	}
    else fprintf(sauv_det,"hard\n");

fclose(sauv_det);
}
else printf("Impossible de creer le fichier sauv_det.txt\n");

}
void affiche_stat()
{
   Victoire victoire;
    int pos=0, fin=0;

 FILE* fichier_stat = NULL;
 fichier_stat = fopen("fichier_stat.txt", "r");

     if (fichier_stat!= NULL)
    {

            fseek(fichier_stat, 0, SEEK_END); //  *
            fin = ftell(fichier_stat);        //  * pour determiner la fin du fichier (le nombre de carateres totale)
            fseek(fichier_stat, 0, SEEK_SET); //on retourne le curseur au début du fichier
            //Color(0,8);
            printf("_________________________________________________________________________________________\n");
            printf("\033[32m");
            printf(" PionDuGagnat                NomGagnant              NomPerdant              Niveau\n");
            printf("\033[00m");
            printf("_________________________________________________________________________________________\n");
            //Color(7, 0);
            while (pos<(fin-2)) //fin - \n (qui represente 2 caracteres)
            {

                fscanf(fichier_stat,"%s %s %s %s",&victoire.pionG,&victoire.nomG,&victoire.nomP,&victoire.niveau); //le libelle doit etre au dernier emplacement pour que le programme fonctionne correctement

                printf(" %10s                 %10s             %10s           %10s\n", &victoire.pionG,&victoire.nomG,&victoire.nomP,&victoire.niveau);
                printf("_________________________________________________________________________________________\n");
                pos=ftell(fichier_stat); //position de la fin de chaque ligne lue
                fseek(fichier_stat, (pos+2), SEEK_SET); //pos + \n (qui representent 2 caracteres)


            }

            fclose(fichier_stat);

    }

    else
    {
        printf("Impossible d'ouvrir le fichier fichier_caissier.txt");
    }

}



#endif
