#ifndef GAME_HEADER
#define GAME_HEADER

#include "strategy.h"
#include "bus.h"
#include "player.h"
#include "station.h"

#define NOMBRE_MAX_STATIONS 10
#define NOMBRE_STATIONS_DEBUT 3

#define MAX_TURN 500

int monID;

typedef struct Station Station;
typedef struct Player Player;

typedef struct Game{
    int nbPlayers;
    int turn;
    int nbStation;

    Station* stations;
    Player* players;
}Game;

void freeGame(Game* game);
void getServerDataFirstTurn(Game* game);
void getServerDataEveryTurn(Game* game);
int gameEnded(Game* game);
Game* initGame();


#endif