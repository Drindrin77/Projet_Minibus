/*
Au premier tour, on recupere uniquement les infos du premier tour et on initialise tous les structures.
Puis a chaque tour on effectue le meme programme dans cet ordre:
-Recuperation de tous les donnees envoyés par le serveur
-Analyse du jeu
-Envoi de la commande

Comment fonctionne mon IA :
    A chaque tour, après avoir récuperer les données, on achete des améliorations:

    -En premier, on achete des bus jusqu'à en avoir le max. On l'achete si on a assez d'argent 
        et on le place à la station qui possède le plus de voyageur. 
        Ainsi si toutes les stations sont vides, on ne réalise aucun achat.
    -Puis une fois les 4 bus obtenus, on achete au max l'amelioration SP (augmente la vitesse des bus)
    -Puis une fois qu'on a amélioré au max la vitesse des bus, on augmente au max l'amelioration CT (prix du billet)

    Une fois les améliorations achetés ou non, on dirige les bus.
    Chaque bus possede la variable canChangeDestination. Cette variable va nous permettre de savoir si le bus peut 
    à nouveau changer de destination.
    
    -On check si le bus peut changer de destination.
        Si oui, on récupere l'id de la station où il va aller et on change cette variable à 0 (false)
        On précéde ainsi pour calculer la station :
            -Si le bus possède des voyageurs, il ira à la station souhaitée la plus proche
            -Sinon il ira à la station non vide la plus proche.

    On stocke toutes les commandes dans une variable.
    A la fin de ces opérations, on envoit la/les commande(s). 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//CONSTANTES

#define MAX_PASSENGER_GETTING_OFF_BUS 5
#define NB_MAX_PASSENGER_IN_BUS 5
#define MAX_TURN 500
#define MAX_STATIONS 10
#define NB_STATIONS_START 3
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

int myID;

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
    int canChangeDestination;
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
    int capacity; //not used
    int nbPassager;
    LLPassenger* waitingPassengers;
}Station;

//Structure qui contient tous les données du jeu.
typedef struct Game{
    int nbPlayers;
    int turn;
    int nbStation;

    Station* stations;
    Player* players;
}Game;

//Structure qui permet de simplifier la mise en place de la strategie.
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
int busCanChangeDestination(Bus b, Station s);
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
LLPassenger* deletePassenger(int idPassenger, LLPassenger* passengers,int freeP);
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
int getIDStationWithMostPassenger(Station* stations, int nbStations);
void getServerDataStation(Game* game);

/*
*   SIGNATURE STRATEGY
*/
void freeStrategy(Strategy* s);
Strategy* initStructStrategy(Game* game);
void play(Game* game);
void everyTurnStrategy(Strategy* s);
void updateCanChangeDestination(Strategy* strat);
void changeDestinationBuses(Strategy* strat);
void buyImprovements(Strategy* s);

/*
*   FUNCTIONS COMMANDS
*/
void freeCommands(char** commands, int size){
    for(int i = size-1 ; i > 0 ; i--){
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

//On envoie dans la sortie standard la liste des commandes stockée dans commands
//commands contient forcement au moins la commande PASS
void sendCommands(char** commands, int nbcommand){
    char* resultat = (char*)malloc(sizeof(char)*(nbcommand*MAX_SIZE_COMMAND_NAME));
    strcpy(resultat,commands[0]);
    for(int i = 1 ; i < nbcommand ; i++){
        strcat(resultat,";");
        strcat(resultat,commands[i]);
    }
    printf("%s\n",resultat);
    free(resultat);
}

/*
    Liste des fonctions qui renvoient la chaine de caractere qui correspond
    à la commande qui permet d'effectuer l'action
*/
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

/*
    LISTE DES CONDITIONS DES AMELIORATIONS
    Renvoie 1 si on peut effectuer l'amelioration
    0 sinon
*/
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
    if(p.argent < PRICE_UPGRADE_SB || p.SB == MAX_INCREASE_SB)
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
*   FUNCTIONS BUS
*/
void freeBus(Bus* b){
    freeLLPassengers(b->passengers);
    free(b);
}

void addBus(Bus* buss, Bus b, int nbBus){
    buss[nbBus].ID = b.ID;
    buss[nbBus].nbCar = b.nbCar;
    buss[nbBus].IDStationDest = b.IDStationDest;
    buss[nbBus].position.X = b.position.X;
    buss[nbBus].position.Y = b.position.Y;
    buss[nbBus].canChangeDestination = 1;
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

//Renvoie le bus qui possede le passenger dont l'id est envoyé en parametre
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
//Renvoie le bus du joueur p dont l'id du bus correspond à idBus
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
            addBus(p->bus, b, p->nbBus);
            p->nbBus++;
        }
        //Sinon on met a jour les donnees du bus
        else{
            Bus* bToUpdate = getBusOfPlayerByIDBus(*p,b.ID);
            updateDataBus(bToUpdate,b);
        }
    }
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
//Verifie si la LLPassenger contient le passenger dont l'id est envoyé en parametre
int containPassenger(LLPassenger* l, int idPassenger){
    LLPassenger* tmp = l;
    while(tmp!=NULL){
        if(tmp->p.ID == idPassenger)
            return 1;
        tmp=tmp->next;
    }
    return 0;
}

//On obtient ici la liste des stations que les voyageurs souhaitent aller
Station* getStationsOfPassengers(Station* stations, int nbStation, LLPassenger* l, int nbPassenger){
    Station* stationsPassengers = (Station*)malloc(sizeof(Station)*nbPassenger);
    LLPassenger* tmp = l;
    int i = 0;
    while(tmp!=NULL){
        Station* s = getStationByIDStation(stations,nbStation,tmp->p.IDS2);
        addStation(stationsPassengers,*s,i);
        tmp=tmp->next;
        i++;
    }
    return stationsPassengers;
}
//Nombre d'element dans la LLPassenger
int nbPassenger(LLPassenger* l){
    LLPassenger* tmp = l;
    int nb = 0;
    while(tmp!=NULL){
        tmp=tmp->next;
        nb++;
    }
    return nb;
}

//Nombre de voyageur qui veulent descendre du bus
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
//On retourne la nouvelle LLPassenger qui ne possède plus le Passenger 
LLPassenger* deletePassenger(int idPassenger, LLPassenger* passengers, int freeP){
    LLPassenger* tmp = passengers;
    LLPassenger* prev; 
    // Si le Passenger a supprimé est en tete de liste 
    if (tmp != NULL && tmp->p.ID == idPassenger) 
    { 
        prev = tmp->next;   // Changed head 
        if(freeP==1)
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
        if(freeP==1)
            free(tmp);  // Free memory 

        return passengers;
    }
    
}
//On traite ici des voyageurs qui sont montés dans un bus
//On supprime le Passenger de la liste d'attente sans le free et on l'ajoute
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

//On traite ici des voyageurs qui sont descendus d'un bus
//On recherche le bus qui contient le Passenger qui descend.
//On free le Passenger pour le faire disparaitre du jeu
void processPassengersGettingOff(Game* game){
    int idt;
    scanf("%d", &idt);
    Bus* buss = getBusByIdP(game->players,idt,game->nbPlayers);
    if(buss!=NULL)
        buss->passengers=deletePassenger(idt,buss->passengers,1);
}
//Traitement des nouveaux passengers,
//on les ajoute dans la liste des passengers du station où ils
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
            addStation(result,stations[i],counter);
            counter++;
        }
    }
    *nbStation = counter;
    return result;
}
 
//Ajoute une nouvelle station dans la liste
void addStation(Station* stations, Station s, int nbStation){
    stations[nbStation].ID = s.ID;
    stations[nbStation].position.X = s.position.X;
    stations[nbStation].position.Y = s.position.Y;
    stations[nbStation].capacity = s.capacity;
}
//1 entier: info si nouvelle station (1 oui, 0 non)
//4 entiers: ID, X, Y , capacite d'une NOUVELLE station
void getServerDataStation(Game* game){
    int newStation;

    //Indique s'il y a une nouvelle station
    scanf("%d", &newStation);
    Station s; 
    
    //Si nouvelle station, alors l'ajouter dans la liste, sinon ne fais rien
    if(newStation == 1){    
        scanf("%d %d %d %d", &s.ID, &(s.position.X), &(s.position.Y), &s.capacity);
        addStation(game->stations, s, game->nbStation);
        game->nbStation++;
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
    Player* me = getPlayer(game->players,myID,game->nbPlayers);
    char** commands = initCommands();    

    strat->me = me;
    strat->commands = commands;
    strat->game = game;

    return strat;
}

//Calcul qui nous permet de déterminer le nombre de tour qui reste pour remplir le bus
int ceiling(int n){
    return (n + MAX_PASSENGER_GETTING_OFF_BUS - 1) / MAX_PASSENGER_GETTING_OFF_BUS;
}

//Verifie si le bus peut de nouveau changer de direction
int busCanChangeDestination(Bus b, Station s){
    //Si le bus est arrive à la station demande précédemment
    if(samePosition(b.position,s.position)==1){
        //Si plus aucun voyageur ne souhaite descendre
        if( nbPassengersGettingOffBus(s.ID,b.passengers) == 0){
            int nbPassengerInBus = nbPassenger(b.passengers);
            
            //BUS PLEIN
            if(nbPassengerInBus == b.nbCar*NB_MAX_PASSENGER_IN_BUS)
                return 1;

            int nbPassengerInStation = nbPassenger(s.waitingPassengers);
            int nbTurnToFill;
            int nbPassengerToFill = (b.nbCar*NB_MAX_PASSENGER_IN_BUS) - nbPassengerInBus;

            //On calcul le nombre de tours necessaire pour remplir le bus
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


void updateBusCanChangeDestination(Strategy* strat){

    Bus* myBuses = strat->me->bus;
    int nbStation = strat->game->nbStation;
    
    for(int i = 0; i < strat->me->nbBus ; i++){
        Station* s = getStationByIDStation(strat->game->stations,nbStation,myBuses[i].IDStationDest);
        if(busCanChangeDestination(myBuses[i],*s) == 1 )
            myBuses[i].canChangeDestination = 1;
    }
}

//Pour chacun de mes bus, si le bus peut changer de destination
//On regarde si le nombre de voyageurs dans le bus est vide.
//Si le bus n'est pas vide, on recupere la station non vide la plus proche
//Sinon on recupere la station la plus proche d'un voyageur du bus
//A la fin on ajoute la commande qui permet d'aller à la station voulue 
void changeDestinationBuses(Strategy* strat){
    Station* s;
    Bus* myBuses = strat->me->bus;
    Station* stations = NULL;
    int nbStations = 0;

    for(int i = 0 ; i < strat->me->nbBus ; i++){
        //Si le bus peut changer de destination
        if(myBuses[i].canChangeDestination == 1){
            int nbP = nbPassenger(myBuses[i].passengers);
            //Si le bus n'est pas vide
            if(nbP != 0){
                stations = getStationsOfPassengers(strat->game->stations, 
                                        strat->game->nbStation, myBuses[i].passengers, nbP);
                nbStations = nbP;
            }
        
            else{
                nbStations = strat->game->nbStation;
                stations = getStationsNotEmpty(strat->game->stations, &nbStations);
            }
            //Check dans le cas s'il y a pas de voyageur dans le bus et que toutes les stations sont vides 
            if(nbStations != 0){
                s=getClosestStation(myBuses[i].position, stations, nbStations);
                myBuses[i].canChangeDestination = 0;
                addCommand(strat,command_directBus(myBuses[i].ID,s->ID));
            }
        }
    }

    free(stations);
}

//On achete des que possible les ameliorations dans cet ordre:
//Achat des bus jusqu'à en avoir le max
//Une fois les 4 bus obtenu, on achete au max l'amelioration SP
//Une fois le max amelioration de SP, on achete au max l'amelioration CT
void buyImprovements(Strategy* s){

    if(canAddBus(*(s->me)) == 1){
        int idStation = getIDStationWithMostPassenger(s->game->stations, s->game->nbStation);
        if(idStation != -1) //Verification au cas où toutes les stations sont vides
            addCommand(s,command_addBus(idStation));
    }
   
    if(s->me->nbBus == MAX_NB_BUS && canUpgradeSP(*(s->me)) == 1)
        addCommand(s,command_upgradeSP());

    if(s->me->SP == MAX_INCREASE_SP && canUpgradeCT(*(s->me)) == 1)
        addCommand(s,command_upgradeCT());
}

void everyTurnStrategy(Strategy* s){
    buyImprovements(s);
    if(s->me->nbBus != 0){
        updateBusCanChangeDestination(s);
        changeDestinationBuses(s);
    }
    addCommand(s,command_pass());
}

void play(Game* game){
    Strategy* strat = initStructStrategy(game);
    everyTurnStrategy(strat);
    sendCommands(strat->commands,strat->nbCommand);
    freeStrategy(strat);
}


/*
*   FUNCTIONS GAME
*/

void freeGame(Game* game){
    freeStations(game->stations);   
    freePlayers(game->players);
    free(game);
}

//Recupere les infos du premier tour de jeu 
void getServerDataFirstTurn(Game* game){
    scanf("%d %d", &game->nbPlayers, &myID);
    Station s;
    for(int i = 0 ; i < NB_STATIONS_START ; i++){
        scanf("%d %d %d %d", &(s.ID), &(s.position.X), &(s.position.Y), &(s.capacity));
        addStation(game->stations,s,game->nbStation);
        game->nbStation++;
    }
}

//recupere les infos à chaque tour (premier tour exclu)
void getServerDataEveryTurn(Game* game){
    getServerDataPlayer(game);
    getServerDataStation(game);
    getServerDataBus(game);
    getServerDataPassenger(game);
}

//Initialisation du jeu
Game* initGame(){
    Game* game = (Game*)malloc(sizeof(Game));
    game->stations = (Station*)malloc(sizeof(Station)*MAX_STATIONS);
    getServerDataFirstTurn(game);
    initPlayer(game);
    return game; 
}

//Verifie si le jeu est terminé
//Donc si le tour a atteint le 
int gameEnded(Game* game){
    Player* p = getPlayer(game->players, myID, game->nbPlayers);
    if(game->turn < MAX_TURN && p->victoire == 0)
        return 0;
    return 1;
}

// LAUNCH GAME

int main(){
    Game* game = initGame(); // First turn completed
    do{
        getServerDataEveryTurn(game);
        play(game);
        fflush(stdout);
        game->turn++;
    }while(gameEnded(game) == 0);
        
    freeGame(game);
}