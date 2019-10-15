#ifndef GAME_HEADER
#define GAME_HEADER

#include "bus.h"
#include "joueur.h"
#include "station.h"
#include "voyageur.h"

#define NOMBRE_STATION_DEBUT 3

#define MAX_NOMBRE_BUS 4

int monID;

typedef struct Station Station;
typedef struct Joueur Joueur;
typedef struct ListeVoyageur ListeVoyageur;

typedef struct Jeu{
    int nbJoueur;
    int tour;
    int nbStation;

    Station* stations;
    Joueur* joueurs;
    ListeVoyageur* voyageursEnAttente;
}Jeu;

void recupereDonneePremierTour(Jeu* j);
void recupererDonneeChaqueTour(Jeu* jeu);
Jeu* initialiserJeu();

#endif