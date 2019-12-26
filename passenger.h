#ifndef PASSENGER_HEADER
#define PASSENGER_HEADER

#include "game.h"

typedef struct Passenger{
    int ID;
    int IDS1;
    int IDS2;
}Passenger;

typedef struct LLPassenger{
    Passenger p;
    struct LLPassenger* next;
}LLPassenger;

typedef struct Station Station;
typedef struct Game Game;

void freeLLPassengers(LLPassenger* head);
LLPassenger* createPassenger(LLPassenger* suivant, Passenger* v);
LLPassenger* deletePassenger(int idPassenger, LLPassenger* passengers,int liberer);
int containPassenger(LLPassenger* l, int idPassenger);
Passenger* getPassenger(LLPassenger* passengers, int ID);
int nbPassenger(LLPassenger* l);
int nbPassengersGettingOffBus(int idStation, LLPassenger* l);
Station* getStationsOfPassengers(Station* stations, int nbStation, LLPassenger* l, int nbPassenger);
void processNewPassengers(Game* game);
void processPassengersGettingOff(Game* game);
void processPassengersGettingOn(Game* game);
void getServerDataPassenger(Game* game);

#endif
