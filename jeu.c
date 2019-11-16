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
    Station s;
    for(int i = 0 ; i < NOMBRE_STATIONS_DEBUT ; i++){
        scanf("%d %d %d %d", &(s.ID), &(s.position.X), &(s.position.Y), &(s.capacite));
        j->nbStation++;
        addStation(j->stations,s,j->nbStation);
    }
}

void recupererDonneeChaqueTour(Jeu* jeu){
    recupereDonneeJoueurs(jeu); //Recupere les scanf dans le fichier joueur.c
    getServerDataStation(jeu); //Recupere les scanf dans le fichier station.c
    recupereDonneeBus(jeu); //recupere les scanf dans le fichier bus.c
    recupereDonneeVoyageur(jeu); //recupere les scanf dans le fichier voyageur.c
}

Jeu* initialiserJeu(){
    Jeu* jeu = (Jeu*)malloc(sizeof(Jeu));
    jeu->stations = (Station*)malloc(sizeof(Station)*NOMBRE_MAX_STATIONS);
    jeu->nbStation = 0;
    recupereDonneePremierTour(jeu);
    jeu->joueurs = (Joueur*)malloc(sizeof(Joueur)*jeu->nbJoueur);
    for(int i = 0 ; i < jeu->nbJoueur ; i++){
        jeu->joueurs[i].bus = (Bus*)malloc(sizeof(Bus)*MAX_NOMBRE_BUS);   
        jeu->joueurs[i].nbBus = 0;
    }
    return jeu; 
}

int main(){
    Jeu* jeu = initialiserJeu();
    jeu->tour=0;
    while(jeu->tour<500){
        recupererDonneeChaqueTour(jeu);
        fflush(stderr);
        start(jeu);
        fflush(stdout);
        jeu->tour++;
    }
}