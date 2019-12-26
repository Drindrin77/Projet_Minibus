#include "station.h"

void freeStations(Station* stations){
    freeLLPassengers(stations->waitingPassengers);
    free(stations);
}

int getIDStationWithMostPassenger(Station* stations, int nbStations){
    int tmp = 0;
    int id = 0;

    for(int i = 0 ; i < nbStations ; i++){
        int nbP = nbPassenger(stations[i].waitingPassengers);
        if(nbP > tmp){
            tmp = nbP;
            id = stations[i].ID;
        }
    }
    if(tmp == 0)
        return -1;
    return id;
}

Station* getStationByIDStation(Station* stations, int nbStation, int idStation){
    for(int i = 0 ; i < nbStation ; i++){
        if(stations[i].ID == idStation)
            return &(stations[i]);
    }
    return NULL;
}

Station* getStationByIdP(Station* stations, int nbStation, int idPassenger){
    for(int i = 0 ; i < nbStation ; i++){
        if(containPassenger(stations[i].waitingPassengers,idPassenger)==1)
            return &(stations[i]);
    }
    return NULL;
}

void displayStations(Station* stations, int nbStation){
    for(int i = 0 ; i < nbStation ; i++){
        fprintf(stderr,"displayStations ID Station %d\n",stations[i].ID);
    }
}

//NBSTATION != 0
Station* getClosestStation(Position pBus, Station* stations, int nbStation){
    
    double tmp;
    double distanceMin = distancePositions(pBus,stations[0].position);
    Station* s = &(stations[0]);

    for(int i = 1 ; i < nbStation ; i++){
        tmp = distancePositions(pBus,stations[i].position);
        if(tmp<distanceMin){
            distanceMin = tmp;
            s=&(stations[i]);
        }
    }
    return s;
}

Station* getStationsNotEmpty(Station* stations, int* nbStation){
    int nb;
    int counter = 0;
    Station* result = (Station*)malloc(sizeof(Station)*(*nbStation));

    for(int i = 0 ; i < *nbStation ; i++){
        nb = nbPassenger(stations[i].waitingPassengers);
        if(nb != 0){
            counter++;
            addStation(result,stations[i],counter);
        }
    }
    *nbStation = counter;
    return result;
}
 
//Ajoute une nouvelle station dans la liste
void addStation(Station* stations, Station s, int nbStation){
    stations[nbStation-1].ID = s.ID;
    stations[nbStation-1].position.X = s.position.X;
    stations[nbStation-1].position.Y = s.position.Y;
    stations[nbStation-1].capacity = s.capacity;
}
//1 entier: info si nouvelle station ( 1 oui, 0 non)
//4 entiers: ID, X, Y , capacite d'une NOUVELLE station
void getServerDataStation(Game* game){
    int newStation;

    //Indique s'il y a une nouvelle station
    scanf("%d", &newStation);
    Station s; 
    
    //Si nouvelle station, alors l'ajouter dans la liste, sinon ne fais rien
    if(newStation == 1){    
        scanf("%d %d %d %d", &(s.ID), &(s.position.X), &(s.position.Y), &(s.capacity));
        game->nbStation++;
        addStation(game->stations, s, game->nbStation);
    }
}