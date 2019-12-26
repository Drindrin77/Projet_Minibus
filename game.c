#include "game.h"
#include <stdio.h>
#include <stdlib.h>
/*
Recuperation des valeurs avant le premier tour
1 ligne : 2 entiers (NJ J) -> Le nombre de joueurs et le numéro du joueur
3 lignes 4 entiers (ID X Y K ) -> ID, coordonée X, Y et capacité de la station
*/

void freeGame(Game* game){
    freeStations(game->stations);   
    freePlayers(game->players);
    free(game);
}

void getServerDataFirstTurn(Game* game){
    scanf("%d %d", &game->nbPlayers, &monID);
    Station s;
    for(int i = 0 ; i < NOMBRE_STATIONS_DEBUT ; i++){
        scanf("%d %d %d %d", &(s.ID), &(s.position.X), &(s.position.Y), &(s.capacity));
        game->nbStation++;
        addStation(game->stations,s,game->nbStation);
    }
}

void getServerDataEveryTurn(Game* game){
    getServerDataPlayer(game); //Recupere les scanf dans le fichier joueur.c
    getServerDataStation(game); //Recupere les scanf dans le fichier station.c
    getServerDataBus(game); //recupere les scanf dans le fichier bus.c
    getServerDataPassenger(game); //recupere les scanf dans le fichier voyageur.c
}

Game* initGame(){
    Game* game = (Game*)malloc(sizeof(Game));
    game->stations = (Station*)malloc(sizeof(Station)*NOMBRE_MAX_STATIONS);
    getServerDataFirstTurn(game);
    initPlayer(game);
    return game; 
}

int gameEnded(Game* game){
    Player* p = getPlayer(game->players, monID, game->nbPlayers);
    if(game->turn < MAX_TURN && p->victoire == 0)
        return 0;
    return 1;
}

int main(){
    Game* game = initGame();
    do{
        getServerDataEveryTurn(game);
        startStrategy(game);
        fflush(stdout);
        game->turn++;
    }while(gameEnded(game) == 0);
        
    freeGame(game);
}


