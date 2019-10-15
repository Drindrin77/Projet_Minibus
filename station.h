#ifndef STATION_HEADER
#define STATION_HEADER

#include "jeu.h"
#include "voyageur.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct ListeVoyageur ListeVoyageur;

typedef struct Station{
    int ID;
    int X;
    int Y;
    int capacite;
    int nbPassager;
    ListeVoyageur* voyageursEnAttente;
}Station;

Station* recupereStationParIdVoyageur(Station* stations, int nbStation, int idVoyageur);
Station* recupereStationParIdStation(Station* stations, int nbStation, int idStation);
void ajouterNouvelleStation(Station* stations, Station s, int nbStation);
void recupereDonneeStations(Jeu* jeu);

#endif