#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//CONSTANTES

#define MAX_PASSENGER_GETTING_OFF_BUSS 5
#define MAX_TURN 500
#define NOMBRE_MAX_STATIONS 10
#define NOMBRE_STATIONS_DEBUT 3
#define MAX_SIZE_COMMAND_NAME 20
#define MAX_SIZE_COMMANDS 20
#define PRICE_ADD_BUS 100
#define PRICE_INCREASE_SIZE_BUS 50
#define PRICE_UPGRADE_SB 100
#define PRICE_UPGRADE_SP 200
#define PRICE_UPGRADE_CT 100
#define MAX_INCREASE_CT 5
#define MAX_INCREASE_SP 2
#define MAX_INCREASE_SB 2
#define MAX_NB_BUS 4

int monID;

//STRUCTURES

typedef struct Passenger{
    int ID;
    int IDS1;
    int IDS2;
}Passenger;

typedef struct LLPassenger{ //LinkedList Passenger
    Passenger p;
    struct LLPassenger* next;
}LLPassenger;

typedef struct Position{
    int X;
    int Y;        
}Position;

typedef struct Bus{
    int ID;
    Position position;
    int IDStationDest;
    int nbCar; 
    int canMove;
    LLPassenger* passengers;
}Bus;

typedef struct Player{
    int ID;
    int SB; //nb upgrade of SB (more car for buses)
    int SP; //same for SP (upgrade speed of buses)
    int CT; //same for CT (increase prize for passengers)
    int argent;
    int nbBus;
    int victoire;
    Bus* bus;
}Player;

typedef struct Station{
    int ID;
    Position position;
    int capacite;
    int nbPassager;
    LLPassenger* waitingPassengers;
}Station;

typedef struct Game{
    int nbPlayers;
    int turn;
    int nbStation;

    Station* stations;
    Player* players;
}Game;

typedef struct Strategy{
    Game* game;
    int nbCommand;
    char** commands;
    Player* me;
}Strategy;

/*
*   SIGNATURE BUS
*/
void freeBus(Bus* bus);
void addBus(Bus* buss, Bus b, int nbBus);
int containBus(Bus* buss, int idBus, int nbBus);
Bus* getBusByIdP(Player* players, int idVoyageur, int nbPlayers);
int busCanMove(Bus b, Station s);
Bus* getBusByIdBus(Player* players, int idBus, int nbPlayers);
void getServerDataBus(Game* game);

/** 
 *  SIGNATURE COMMAND
 *
 **/
void freeCommands(char** commands, int size);
void sendCommands(char** commands, int nbcommand);
char** initCommands();
void addCommand(Strategy* strat, char* c);

//ALL THE COMMANDS POSSIBLE TO USE
char* command_addBus(int idStation);
char* command_directBus(int idBus, int idStation);
char* command_increaseSizeBus(int idBus);
char* command_upgradeSB();
char* command_upgradeSP();
char* command_upgradeCT();
char* command_pass();

//EVERY VERIFICATION OF IMPROVEMENT
int canAddBus(Player p);
int canIncreaseSizeBus(Player p, Bus bus);
int canUpgradeSB(Player p);
int canUpgradeSP(Player p);
int canUpgradeCT(Player p);

/**
 * SIGNATURE GAME
 **/ 

void freeGame(Game* game);
void getServerDataFirstTurn(Game* game);
void getServerDataEveryTurn(Game* game);
int gameEnded(Game* game);
Game* initGame();

/*
* SIGNATURE PASSENGER
*/

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

/*
*   SIGNATURE PLAYER
*/
Player* getPlayer(Player*,int,int);
void getServerDataPlayer(Game*);
void initPlayer(Game*);
void freePlayers(Player* p);

/*
*   SIGNATURE POSITION
*/
double distancePositions(Position pos1, Position pos2);
int samePosition(Position pos1, Position pos2);

/*
*   SIGNATURE STATION
*/
void freeStations(Station* stations);
Station* getStationByIdP(Station* stations, int nbStation, int idPassenger);
Station* getStationByIDStation(Station* stations, int nbStation, int idStation);
void addStation(Station* stations, Station s, int nbStation);
Station* getClosestStation(Position pBus, Station* stations, int nbStation);
Station* getStationsNotEmpty(Station* stations, int* nbStation);
void getServerDataStation(Game* game);

/*
*   SIGNATURE STRATEGY
*/
void freeStrategy(Strategy* s);
Strategy* initStructStrategy(Game* game);
void startStrategy(Game* game);
void firstTurn(Strategy* s);
void everyTurn(Strategy* s);
void updateBusCanMove(Strategy* strat);
void moveBuses(Strategy* strat);
void buyImprovements(Strategy* s);

/*
*   FUNCTIONS BUS
*/
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

void getServerDataBus(Game* game){
    Bus b;
    int nbBus,idPlayer;
    scanf("%d", &nbBus);

    //ID J X Y A S: bus, idPlayer, position X Y, id Station, nbCar
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


/*
*   FUNCTIONS COMMAND
*/
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

/*
*   FUNCTIONS GAME
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
        scanf("%d %d %d %d", &(s.ID), &(s.position.X), &(s.position.Y), &(s.capacite));
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

/*
*   FUNCTIONS PASSENGER
*/
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

/*
*   FUNCTION PLAYER
*/

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

/*
*   FUNCTION POSITION
*/

double distancePositions(Position pos1, Position pos2){
    return sqrt(pow(pos2.X-pos1.X,2) + pow(pos2.Y - pos1.Y,2));
}

int samePosition(Position pos1, Position pos2){
    if(pos1.X==pos2.X && pos1.Y == pos2.Y)
        return 1;
    return 0;
}

/*
*   FUNCTION STATION
*/

void freeStations(Station* stations){
    freeLLPassengers(stations->waitingPassengers);
    free(stations);
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


//resultne la station qui est le moins loin du bus donné en parametre
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
    Station* result = (Station*)malloc(sizeof(Station)*(*nbStation));

    for(int i = 0 ; i < *nbStation ; i++){
        nb = nbPassenger(stations[i].waitingPassengers);
        if(nb != 0){
            counter++;
            addStation(result,stations[i],counter);
        }
    }
    result = (Station*)realloc(result,counter);
    *nbStation = counter;
    return result;
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
void getServerDataStation(Game* game){
    int nouvelleStation;

    //Indique s'il y a une nouvelle station
    scanf("%d", &nouvelleStation);
    Station s; 
    
    //Si nouvelle station, alors l'ajouter dans la liste, sinon ne fais rien
    if(nouvelleStation == 1){    
        scanf("%d %d %d %d", &s.ID, &(s.position.X), &(s.position.Y), &s.capacite);
        game->nbStation++;
        addStation(game->stations, s, game->nbStation);
    }
}

/*
*   FUNCTION STRATEGY
*/

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
   
void firstTurn(Strategy* s){
    addCommand(s,command_addBus(0));
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
        }
    }

    free(stations);
}

void buyImprovements(Strategy* s){

    if(canAddBus(*(s->me)) == 1) //Des qu'on peut on achete jusqu'a posséder 4 bus{}
        addCommand(s,command_addBus(0));
   
    if(s->me->nbBus == MAX_NB_BUS && canUpgradeSP(*(s->me)) == 1) //Des qu'on a 4 bus, on ameliore la vitesse
        addCommand(s,command_upgradeSP());

    if(s->me->SP == MAX_INCREASE_SP && canUpgradeCT(*(s->me)) == 1)
       addCommand(s,command_upgradeCT());
}

void everyTurn(Strategy* s){
    
    buyImprovements(s);
    updateBusCanMove(s); //Check si les bus sont arrives a destination ou non puis met a jour les variables
    moveBuses(s);
    addCommand(s,command_pass());
}

void startStrategy(Game* game){

    Strategy* strat = initStructStrategy(game);

    if(game->turn == 0)
        firstTurn(strat);
    else
        everyTurn(strat);

    sendCommands(strat->commands,strat->nbCommand);
    freeStrategy(strat);
}

// LAUNCH GAME

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