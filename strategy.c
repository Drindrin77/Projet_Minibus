#include "strategy.h"

void freeStrategy(Strategy* s){
    freeCommands(s->commands,s->nbCommand);
    free(s);
}

Strategy* initStructStrategy(Game* game){
    Strategy* strat = (Strategy*)malloc(sizeof(Strategy));
    Player* me = getPlayer(game->players,monID,game->nbPlayers);
    char** commands = initCommands();    

    strat->me = me;
    strat->commands = commands;
    strat->game = game;

    return strat;
}

void updateBusCanMove(Strategy* strat){

    Bus* myBuses = strat->me->bus;
    int nbStation = strat->game->nbStation;
    
    for(int i = 0; i < strat->me->nbBus ; i++){
        Station* s = getStationByIDStation(strat->game->stations,nbStation,myBuses[i].IDStationDest);
        if(busCanMove(myBuses[i],*s) == 1 )
            myBuses[i].canMove = 1;
    }
}

void moveBuses(Strategy* strat){
    Station* s;
    Bus* myBuses = strat->me->bus;
    Station* stations = NULL;
    int nbStations = 0;
    for(int i = 0 ; i < strat->me->nbBus ; i++){
        if(myBuses[i].canMove == 1){
            int nbP = nbPassenger(myBuses[i].passengers);
            if(nbP != 0){
                stations = getStationsOfPassengers(strat->game->stations, 
                                        strat->game->nbStation, myBuses[i].passengers, nbP);
                nbStations = nbP;
            }
            else{
                nbStations = strat->game->nbStation;
                stations = getStationsNotEmpty(strat->game->stations, &nbStations);
            }
            if(nbStations != 0){
                s=getClosestStation(myBuses[i].position, stations, nbStations);
                myBuses[i].canMove = 0;
                addCommand(strat,command_directBus(myBuses[i].ID,s->ID));
            }
            free(stations);
        }
    }
}

void buyBusIfPassengers(Strategy* s){
    int idStation = getIDStationWithMostPassenger(s->game->stations, s->game->nbStation);
    if(idStation != -1)
        addCommand(s,command_addBus(idStation));
}

void buyImprovements(Strategy* s){

    if(canAddBus(*(s->me)) == 1)
        buyBusIfPassengers(s);
   
    if(s->me->nbBus == MAX_NB_BUS && canUpgradeSP(*(s->me)) == 1) //Des qu'on a 4 bus, on ameliore la vitesse
        addCommand(s,command_upgradeSP());

    if(s->me->SP == MAX_INCREASE_SP && canUpgradeCT(*(s->me)) == 1)
        addCommand(s,command_upgradeCT());
}

void everyTurnStrategy(Strategy* s){
    
    buyImprovements(s);

    if(s->me->nbBus != 0){
        updateBusCanMove(s);
        moveBuses(s);
    }

    addCommand(s,command_pass());
}

void startStrategy(Game* game){

    Strategy* strat = initStructStrategy(game);
    everyTurnStrategy(strat);
    sendCommands(strat->commands,strat->nbCommand);
    freeStrategy(strat);
}