#include "passenger.h"

void freeLLPassengers(LLPassenger* head){
    LLPassenger* current;
    while ((current = head) != NULL) { // set curr to head, stop if list empty.
        head = head->next;          // advance head to next element.
        free (current);                // delete saved pointer.
    }
}
LLPassenger* createPassenger(LLPassenger* next, Passenger* p){
    LLPassenger* result = (LLPassenger*)malloc(sizeof(LLPassenger));
    result->p.ID = p->ID;
    result->p.IDS1 = p->IDS1;
    result->p.IDS2 = p->IDS2;
    result->next = next;
    return result;
}

Passenger* getPassenger(LLPassenger* passengers, int ID){

    LLPassenger* tmp = passengers;
    while(tmp!=NULL){
        if(tmp->p.ID == ID)
            return &(tmp->p);        
        tmp=tmp->next;
    }
    return NULL;
}

int containPassenger(LLPassenger* l, int idPassenger){
    LLPassenger* tmp = l;
    while(tmp!=NULL){
        if(tmp->p.ID == idPassenger)
            return 1;
        tmp=tmp->next;
    }
    return 0;
}

Station* getStationsOfPassengers(Station* stations, int nbStation, LLPassenger* l, int nbPassenger){
    Station* stationsPassengers = (Station*)malloc(sizeof(Station)*nbPassenger);
    LLPassenger* tmp = l;
    int i = 0;
    while(tmp!=NULL){
        i++;
        Station* s = getStationByIDStation(stations,nbStation,tmp->p.IDS2);
        addStation(stationsPassengers,*s,i);
        tmp=tmp->next;
    }
    return stationsPassengers;
}

int nbPassenger(LLPassenger* l){
    LLPassenger* tmp = l;
    int nb = 0;
    while(tmp!=NULL){
        tmp=tmp->next;
        nb++;
    }
    return nb;
}

int nbPassengersGettingOffBus(int idStation, LLPassenger* l){
    LLPassenger* tmp = l;
    int nb = 0;
    while(tmp!=NULL){
        if(tmp->p.IDS2 == idStation)
            nb++;
        tmp=tmp->next;
    }
    return nb;
}

//Supression du Passenger de la liste donnée en parametre. 
//On indique dans l'entier liberer si on veut supprimer le Passenger du jeu  
//ou juste l'enlever de la liste
LLPassenger* deletePassenger(int idPassenger, LLPassenger* passengers, int liberer){
    LLPassenger* tmp = passengers;
    LLPassenger* prev; 
    // Si le Passenger a supprimé est en tete de liste 
    if (tmp != NULL && tmp->p.ID == idPassenger) 
    { 
        prev = tmp->next;   // Changed head 
        if(liberer==1)
            free(passengers);
        return prev;               // free old head 
    } 
    else{
        while (tmp != NULL && tmp->p.ID != idPassenger) { 
            prev = tmp; 
            tmp = tmp->next; 
        } 
        // Si le Passenger n'était pas dans la liste
        if (tmp == NULL) return NULL; 
        
        prev->next = tmp->next; 
        if(liberer==1)
            free(tmp);  // Free memory 

        return passengers;
    }
    
}
//On supprime le Passenger de la liste d'attente et on l'ajoute
//dans la liste de Passenger du bus du joueur concerné
void processPassengersGettingOn(Game* game){
    int idt, idb;
    scanf("%d %d", &idt, &idb);

    Station* s = getStationByIdP(game->stations,game->nbStation,idt);
    Passenger* v2 = getPassenger(s->waitingPassengers,idt);
    s->waitingPassengers = deletePassenger(idt,s->waitingPassengers,0);
    
    Bus* buss = getBusByIdBus(game->players, idb, game->nbPlayers);
    buss->passengers = createPassenger(buss->passengers,v2);
}


//On recherche le bus qui contient le Passenger qui descend.
//On free le Passenger pour le faire disparaitre du jeu
void processPassengersGettingOff(Game* game){
    int idt;
    scanf("%d", &idt);
    Bus* buss = getBusByIdP(game->players,idt,game->nbPlayers);
    if(buss!=NULL)
        buss->passengers=deletePassenger(idt,buss->passengers,1);
}


//Traitement des nouveaux passengers, on les ajoute dans la liste des passengers du station où ils
//sont apparus
void processNewPassengers(Game* game){
    Passenger p;
    scanf("%d %d %d", &p.ID, &p.IDS1, &p.IDS2);

    Station* s = getStationByIDStation(game->stations,game->nbStation, p.IDS1);
    s->waitingPassengers = createPassenger(s->waitingPassengers,&p);
}


void getServerDataPassenger(Game* game){

    int nbNewPassenger, nbPassengerGetOn, nbPassengerGetOff; 
    scanf("%d %d %d", &nbNewPassenger, &nbPassengerGetOn, &nbPassengerGetOff);   

    for(int i = 0 ; i < nbNewPassenger ; i++)
        processNewPassengers(game);
    
    for(int i = 0 ; i < nbPassengerGetOn ; i++)
        processPassengersGettingOn(game);
    
    for(int i = 0 ; i < nbPassengerGetOff ; i++)
        processPassengersGettingOff(game);
}
