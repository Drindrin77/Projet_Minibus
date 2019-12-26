#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "game.h"
typedef struct Bus Bus;
typedef struct Game Game;

typedef struct Player{
    int ID;
    int SB; //nombre de fois qu'on a ameliore SB
    int SP; //------------------------------- SP
    int CT; //------------------------------- CT
    int argent;
    int nbBus;
    int victoire;
    Bus* bus;
}Player;

Player* getPlayer(Player*,int,int);
void getServerDataPlayer(Game*);
void initPlayer(Game*);
void freePlayers(Player* p);
#endif