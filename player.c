#include "player.h"
#include <stdio.h>
#include <stdlib.h>

void freePlayers(Player* p){
    freeBus(p->bus);
    free(p);
}

void initPlayer(Game* game){
    game->players = (Player*)malloc(sizeof(Player)*game->nbPlayers);
    for(int i = 0 ; i < game->nbPlayers ; i++){
        game->players[i].bus = (Bus*)malloc(sizeof(Bus)*MAX_NB_BUS);   
        game->players[i].nbBus = 0;
    }
}

Player* getPlayer(Player* players, int ID, int nbPlayers){
    for(int i = 0 ; i < nbPlayers ; i++){
        if(players[i].ID == ID){
            return &players[i];
        }
    }
    return NULL;
}


//Recupere les infos des players
//5 entiers : ID joueur, son argent, nombre d'amélioration SB, SP et CT
void getServerDataPlayer(Game* game){
    Player* p ;
    for (int i = 0 ; i < game->nbPlayers ; i++){
        p = &(game->players[i]);
        scanf("%d %d %d %d %d %d", &p->ID, &p->argent, &p->SB, &p->SP, &p->CT, &p->victoire);
    }
}
