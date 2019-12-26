#ifndef COMMAND_HEADER
#define COMMAND_HEADER

#define MAX_SIZE_COMMAND_NAME 20
#define MAX_SIZE_COMMANDS 20

#define PRICE_ADD_BUS 100
#define PRICE_INCREASE_SIZE_BUS 50
#define PRICE_UPGRADE_SB 100
#define PRICE_UPGRADE_SP 200
#define PRICE_UPGRADE_CT 100

#define MAX_INCREASE_CT 5
#define MAX_INCREASE_SP 2
#define MAX_INCREASE_SB 2
#define MAX_NB_BUS 4

#include "game.h"
#include "string.h"

typedef struct Player Player;
typedef struct LLPassenger LLPassenger;
typedef struct Game Game;
typedef struct Strategy Strategy;
typedef struct Bus Bus;

//GESTION MEMOIRE commandS
void freeCommands(char** commands, int size);
void sendCommands(char** commands, int nbcommand);
char** initCommands();
void addCommand(Strategy* strat, char* c);

// LISTE DES commandS POSSIBLES SANS VERIFICATION
char* command_addBus(int idStation);
char* command_directBus(int idBus, int idStation);
char* command_increaseSizeBus(int idBus);
char* command_upgradeSB();
char* command_upgradeSP();
char* command_upgradeCT();
char* command_pass();

// LISTE DES CONDITIONS DES AMELIORATIONS

int canAddBus(Player p);
int canIncreaseSizeBus(Player p, Bus bus);
int canUpgradeSB(Player p);
int canUpgradeSP(Player p);
int canUpgradeCT(Player p);

#endif