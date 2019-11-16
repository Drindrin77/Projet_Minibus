#include "station.h"

Station* getStationByIDStation(Station* stations, int nbStation, int idStation){
    for(int i = 0 ; i < nbStation ; i++){
        if(stations[i].ID == idStation)
            return &(stations[i]);
    }
    return NULL;
}

Station* recupereStationParIdVoyageur(Station* stations, int nbStation, int idVoyageur){
    for(int i = 0 ; i < nbStation ; i++){
        if(contientVoyageur(stations[i].voyageursEnAttente,idVoyageur)==1)
            return &(stations[i]);
    }
    return NULL;
}


//Retourne la station qui est le moins loin du bus donné en parametre
Station* getClosestStation(Position pBus, Station* stations, int nbStation){
    if(nbStation == 0)
        return NULL;

    double tmp;

    double distanceMin = distancePositions(pBus,stations[0].position);
    Station* s = &stations[0];

    for(int i = 1 ; i < nbStation ; i++){
        tmp = distancePositions(pBus,stations[i].position);
        if(tmp<distanceMin){
            distanceMin = tmp;
            s=&stations[i];
        }
    }
    return s;
}

Station* getStationsNotEmpty(Station* stations, int* nbStation){
    int nb;
    int counter = 0;
    Station* retour = (Station*)malloc(sizeof(Station)*(*nbStation));

    for(int i = 0 ; i < *nbStation ; i++){
        nb = nbVoyageur(stations[i].voyageursEnAttente);
        if(nb != 0){
            counter++;
            addStation(retour,stations[i],counter);
        }
    }
    retour = (Station*)realloc(retour,counter);
    *nbStation = counter;
    return retour;
}
 
//Ajoute une nouvelle station dans la liste
void addStation(Station* stations, Station s, int nbStation){
    stations[nbStation-1].ID = s.ID;
    stations[nbStation-1].position.X = s.position.X;
    stations[nbStation-1].position.Y = s.position.Y;
    stations[nbStation-1].capacite = s.capacite;
}
//1 entier: info si nouvelle station ( 1 oui, 0 non)
//4 entiers: ID, X, Y , capacite d'une NOUVELLE station
void recupereDonneeStations(Jeu* jeu){
    int nouvelleStation;

    //Indique s'il y a une nouvelle station
    scanf("%d", &nouvelleStation);
    Station s; 
    
    //Si nouvelle station, alors l'ajouter dans la liste, sinon ne fais rien
    if(nouvelleStation == 1){    
        scanf("%d %d %d %d", &s.ID, &(s.position.X), &(s.position.Y), &s.capacite);
        jeu->nbStation++;
        addStation(jeu->stations, s, jeu->nbStation);
    }
}