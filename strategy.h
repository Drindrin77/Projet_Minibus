#ifndef STRATEGY_HEADER
#define STRATEGY_HEADER

#include "game.h"
#include "command.h"

typedef struct Player Player;
typedef struct Game Game;

//La structure va contenir tous les données du jeu et toutes les commandes.
typedef struct Strategy{
    Game* game;
    int nbCommand;
    char** commands;
    Player* me;
}Strategy;

void freeStrategy(Strategy* s);
Strategy* initStructStrategy(Game* game);
void startStrategy(Game* game);
void everyTurnStrategy(Strategy* s);
void updateBusCanMove(Strategy* strat);
void moveBuses(Strategy* strat);
void buyImprovements(Strategy* s);

#endif