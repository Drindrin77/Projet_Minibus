#ifndef GAME_HEADER
#define GAME_HEADER

#include "bus.h"
#include "joueur.h"
#include "station.h"

#define NOMBRE_MAX_STATIONS 10
#define NOMBRE_STATIONS_DEBUT 3
#define MAX_NOMBRE_BUS 4

int monID;

typedef struct Station Station;
typedef struct Joueur Joueur;

typedef struct Jeu{
    int nbJoueur;
    int tour;
    int nbStation;

    Station* stations;
    Joueur* joueurs;
}Jeu;

void recupereDonneePremierTour(Jeu* j);
void recupererDonneeChaqueTour(Jeu* jeu);
Jeu* initialiserJeu();

#endif