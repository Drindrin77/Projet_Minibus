#ifndef BUS_HEADER
#define BUS_HEADER

#include "game.h"
#include "position.h"

#define MAX_PASSENGER_GETTING_OFF_BUSS 5

typedef struct Player Player;
typedef struct LLPassenger LLPassenger;
typedef struct Game Game;
typedef struct Position Position;
typedef struct Station Station;

typedef struct Bus{
    int ID;
    Position position;
    int IDStationDest;
    int nbCar; // 1 voiture = 5 voyageurs, 2 voiture = 10 ...
    int canMove;
    LLPassenger* passengers;
}Bus;


void addBus(Bus* buss, Bus b, int nbBus);
int containBus(Bus* buss, int idBus, int nbBus);
void getServerDataBus(Game* game);
Bus* getBusByIdP(Player* players, int idVoyageur, int nbPlayers);
int busCanMove(Bus b, Station s);
Bus* getBusByIdBus(Player* players, int idBus, int nbPlayers);
void freeBus(Bus* bus);
#endif