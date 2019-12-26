#include "command.h"
#include <string.h>

void freeCommands(char** commands, int size){
    for(int i = size-1 ; i >= 0 ; i--){
        free(commands[i]);
    }
    free(commands);
}
char** initCommands(){
    char** commands = (char**)malloc(sizeof(char*)*MAX_SIZE_COMMANDS);
    return commands;
}

void addCommand(Strategy* strat, char* c){
    strat->commands[strat->nbCommand] = (char*)malloc(sizeof(char));
    strcpy(strat->commands[strat->nbCommand], c);
    strat->nbCommand++;
}

void sendCommands(char** commands, int nbcommand){
    char* resultat = (char*)malloc(sizeof(char)*(nbcommand*MAX_SIZE_COMMAND_NAME));
    if(nbcommand > 0){
        strcpy(resultat,commands[0]);
        for(int i = 1 ; i < nbcommand ; i++){
            strcat(resultat,";");
            strcat(resultat,commands[i]);
        }
        printf("%s\n",resultat);
        free(resultat);
    }
}

char* command_addBus(int idStation){
    char* command = (char*)malloc(sizeof(char)*MAX_SIZE_COMMAND_NAME);
    snprintf(command,MAX_SIZE_COMMAND_NAME,"BUS %d",idStation);
    return command;
}

char* command_directBus(int idBus, int idStation){
    char* command = (char*)malloc(sizeof(char)*MAX_SIZE_COMMAND_NAME);
    snprintf(command,MAX_SIZE_COMMAND_NAME,"DESTINATION %d %d",idBus,idStation);
    return command;
}
char* command_increaseSizeBus(int idBus){
    char* command = (char*)malloc(sizeof(char)*MAX_SIZE_COMMAND_NAME);
    snprintf(command,MAX_SIZE_COMMAND_NAME,"UPGRADE %d",idBus);
    return command;
}
char* command_upgradeSB(){
    char* command = (char*)malloc(sizeof(char)*9);
    snprintf(command,9,"UPDATESB");
    return command;
}

char* command_upgradeSP(){
    char* command = (char*)malloc(sizeof(char)*9);
    snprintf(command,9,"UPDATESP");
    return command;
}
char* command_upgradeCT(){
    char* command = (char*)malloc(sizeof(char)*9);
    snprintf(command,9,"UPDATECT");
    return command;
}
char* command_pass(){
    char* command = (char*)malloc(sizeof(char)*5);
    snprintf(command,5,"PASS");
    return command;
}
// LISTE DES CONDITIONS DES AMELIORATIONS

int canAddBus(Player p){
    if(p.argent < PRICE_ADD_BUS || p.nbBus == MAX_NB_BUS)
        return 0;
    return 1;
}
int canIncreaseSizeBus(Player p, Bus bus){
    if(p.argent < PRICE_INCREASE_SIZE_BUS || bus.nbCar == p.SB + 1)
        return 0;
    return 1;
}

int canUpgradeSB(Player p){
    if(p.argent < PRICE_UPGRADE_SB || p.SB == MAX_INCREASE_SB) //SB can etre ameliorer 2 fois max
        return 0;
    return 1;
}

int canUpgradeSP(Player p){
    if(p.argent < PRICE_UPGRADE_SP || p.SP == MAX_INCREASE_SP)
        return 0;
    return 1;
}

int canUpgradeCT(Player p){
    if(p.argent < PRICE_UPGRADE_CT || p.CT == MAX_INCREASE_CT)
        return 0;
    return 1;
}