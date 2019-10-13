#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>
/*
Recuperation des valeurs avant le premier tour
1 ligne : 2 entiers (NJ J) -> Le nombre de joueurs et le numéro du joueur
3 lignes 4 entiers (ID X Y K ) -> ID, coordonée X, Y et capacité de la station
*/
void recupereDonneePremierTour(Jeu* j){
    scanf("%d %d", &j->nbJoueur, &monID);
    fprintf(stderr,"Nombre de joueur : %d, monID: %d \n", j->nbJoueur, monID);

    for(int i = 0 ; i < NOMBRE_STATION_DEBUT ; i++){
        scanf("%d %d %d %d", &j->stations[i].ID, &j->stations[i].X, &j->stations[i].Y, &j->stations[i].capacite);
        fprintf(stderr,"Station n°%d\n",i);
        fprintf(stderr,"Id:%d X:%d Y:%d capacite:%d\n", j->stations[i].ID, j->stations[i].X,j->stations[i].Y, j->stations[i].capacite);
    }
}

void recupererDonneeChaqueTour(Jeu* jeu){
    recupereDonneeJoueurs(jeu); //Recupere les scanf dans le fichier joueur.c
    recupereDonneeStations(jeu); //Recupere les scanf dans le fichier station.c
    recupereDonneeBus(jeu); //recupere les scanf dans le fichier bus.c
    recupereDonneeVoyageur(jeu); //recupere les scanf dans le fichier voyageur.c
}

Jeu* initialiserJeu(){
    Jeu* jeu = (Jeu*)malloc(sizeof(Jeu));
    jeu->stations = (Station*)malloc(sizeof(Station)*NOMBRE_STATION_DEBUT);
    recupereDonneePremierTour(jeu);
    jeu->joueurs = (Joueur*)malloc(sizeof(Joueur)*jeu->nbJoueur);
    for(int i = 0 ; i < jeu->nbJoueur ; i++){
        jeu->joueurs[i].bus = (Bus*)malloc(sizeof(Bus)*4);   
    }
    return jeu;
}

int main(){
    Jeu* jeu =initialiserJeu();
    fprintf(stderr,"Commencement de la boucle \n");
    jeu->tour=0;
    while(jeu->tour<500){
        recupererDonneeChaqueTour(jeu);
        fflush(stderr);
        printf("PASS\n");
        fflush(stdout);
        jeu->tour++;
    }
}