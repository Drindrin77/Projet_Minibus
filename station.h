#ifndef STATION_HEADER
#define STATION_HEADER

#include "game.h"
#include "passenger.h"
#include "position.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct LLPassenger LLPassenger;
typedef struct Position Position;

typedef struct Station{
    int ID;
    Position position;
    int capacity; // nbPassengerMax
    LLPassenger* waitingPassengers;
}Station;

void freeStations(Station* stations);
Station* getStationByIdP(Station* stations, int nbStation, int idPassenger);
Station* getStationByIDStation(Station* stations, int nbStation, int idStation);
void addStation(Station* stations, Station s, int nbStation);
Station* getClosestStation(Position pBus, Station* stations, int nbStation);
Station* getStationsNotEmpty(Station* stations, int* nbStation);
int getIDStationWithMostPassenger(Station* stations, int nbStations);
void getServerDataStation(Game* game);
void displayStations(Station* stations, int nbStation);
#endif