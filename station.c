#include "station.h"

//Ajoute une nouvelle station dans la liste
void ajouterNouvelleStation(Station** stations, Station s, int nbStation){
    (*stations)[nbStation-1].ID = s.ID;
    (*stations)[nbStation-1].X = s.X;
    (*stations)[nbStation-1].Y = s.Y;
    (*stations)[nbStation-1].capacite = s.capacite;
}

//1 entier: info si nouvelle station ( 1 oui, 0 non)
//4 entiers: ID, X, Y , capacite d'une NOUVELLE station
void recupereDonneeStations(Jeu* jeu){
    int nouvelleStation;

    //Indique s'il y a une nouvelle station
    scanf("%d", &nouvelleStation);
    fprintf(stderr,"Nouvelle station: %d \n", nouvelleStation);
    Station s; 

    
    //Si nouvelle station, alors l'ajouter dans la liste, sinon ne fais rien
    if(nouvelleStation == 1){
            
    scanf("%d %d %d %d", &s.ID, &s.X, &s.Y, &s.capacite);
    fprintf(stderr,"Info nouvelle station: %d %d %d %d \n", s.ID, s.X, s.Y, s.capacite);
        jeu->nbStation++;
        jeu->stations = (Station*)realloc(jeu->stations,sizeof(Station)*jeu->nbStation);
        ajouterNouvelleStation(&(jeu->stations), s, jeu->nbStation);
    }
}