#ifndef STATION_HEADER
#define STATION_HEADER

#include "jeu.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Station{
    int ID;
    int X;
    int Y;
    int capacite;
    int nbPassager;
}Station;


void ajouterNouvelleStation(Station** stations, Station s, int nbStation);
void recupereDonneeStations(Jeu* jeu);

#endif