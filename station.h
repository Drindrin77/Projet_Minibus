#ifndef STATION_HEADER
#define STATION_HEADER

#include "jeu.h"
#include "voyageur.h"
#include "position.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct ListeVoyageur ListeVoyageur;
typedef struct Position Position;

typedef struct Station{
    int ID;
    Position position;
    int capacite;
    int nbPassager;
    ListeVoyageur* voyageursEnAttente;
}Station;

Station* recupereStationParIdVoyageur(Station* stations, int nbStation, int idVoyageur);
Station* getStationByIDStation(Station* stations, int nbStation, int idStation);
void addStation(Station* stations, Station s, int nbStation);
void recupereDonneeStations(Jeu* jeu);
Station* getClosestStation(Position pBus, Station* stations, int nbStation);
Station* getStationsNotEmpty(Station* stations, int* nbStation);

#endif