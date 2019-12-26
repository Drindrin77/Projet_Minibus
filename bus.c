#include "bus.h"

void freeBus(Bus* b){
    freeLLPassengers(b->passengers);
    free(b);
}

void addBus(Bus* buss, Bus b, int nbBus){
    buss[nbBus-1].ID = b.ID;
    buss[nbBus-1].nbCar = b.nbCar;
    buss[nbBus-1].IDStationDest = b.IDStationDest;
    buss[nbBus-1].position.X = b.position.X;
    buss[nbBus-1].position.Y = b.position.Y;
    buss[nbBus-1].canMove = 1;
}

Bus* getBusByIdBus(Player* players, int idBus, int nbPlayers){
    Player p;
    for(int i = 0 ; i < nbPlayers ; i++){
        p = players[i];
        for(int j = 0 ; j < p.nbBus ; j++){
            if( p.bus[j].ID == idBus)
                return &(p.bus[j]);           
        }
    }
    return NULL;
}

void updateDataBus(Bus* bToUp, Bus b){
    bToUp->nbCar = b.nbCar;
    bToUp->position.X = b.position.X;
    bToUp->position.Y = b.position.Y;
    bToUp->IDStationDest = b.IDStationDest;
}

int containBus(Bus* buss, int idBus, int nbBus){
    for(int i = 0 ; i < nbBus ; i++){
        if(buss[i].ID == idBus)
            return 1;
    }
    return 0;
}

int ceiling(int n){
    return (n + MAX_PASSENGER_GETTING_OFF_BUSS - 1) / MAX_PASSENGER_GETTING_OFF_BUSS;
}

int busCanMove(Bus b, Station s){
    if(samePosition(b.position,s.position)==1){
        if( nbPassengersGettingOffBus(s.ID,b.passengers) == 0){

            int nbPassengerInBus = nbPassenger(b.passengers);
            //BUS PLEIN
            if(nbPassengerInBus == b.nbCar*5)
                return 1;

            int nbPassengerInStation = nbPassenger(s.waitingPassengers);
            int nbTurnToFill;
            int nbPassengerToFill = (b.nbCar*5) - nbPassengerInBus;

            if(nbPassengerInStation<nbPassengerToFill)
                nbTurnToFill = ceiling(nbPassengerInStation);
            else
                nbTurnToFill = ceiling(nbPassengerToFill);

            if(nbTurnToFill == 0)
                return 1;
        }
    }
    return 0;
}

Bus* getBusByIdP(Player* players, int idPassenger, int nbPlayers){

    for(int i = 0 ; i < nbPlayers ; i++){
        for(int j = 0 ; j < players[i].nbBus ; j++){
            Bus* bus = &(players[i].bus[j]);
            if( containPassenger(bus->passengers, idPassenger) == 1)
                return bus;
        }
    }
    return NULL;
}
Bus* getBusOfPlayerByIDBus(Player p, int idBus){
    for(int i = 0 ; i < p.nbBus ; i++){
        if(p.bus[i].ID == idBus)
            return &p.bus[i];
    }
    return NULL;
}

//1 entier : nombre de bus en circulation
//6 entiers : info buss
void getServerDataBus(Game* game){

    int nbBus,idPlayer;
    scanf("%d", &nbBus);

    Bus b;

    //ID J X Y A S: bus, idJoueur le possedant, position X Y du bus, direction id Station, nombre de voiture
    for(int i = 0 ; i < nbBus ; i++){
        scanf("%d %d %d %d %d %d", &b.ID, &idPlayer, &b.position.X, &b.position.Y, &b.IDStationDest, &b.nbCar);

        Player* p = getPlayer(game->players, idPlayer, game->nbPlayers);

        //Si le joueur ne contient pas le bus, l'ajoute
        if( containBus(p->bus, b.ID, p->nbBus) == 0 ){
            p->nbBus++;
            addBus(p->bus, b, p->nbBus);
        }else{
            Bus* bToUpdate = getBusOfPlayerByIDBus(*p,b.ID);
            updateDataBus(bToUpdate,b);
        }
    }
}