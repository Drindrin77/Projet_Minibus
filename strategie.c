#include "strategie.h"

void freeStrategy(Strategie* s){
    freeCommands(s->commands,s->nbCommand);
    free(s);
}

Strategie* initStructStrategie(Jeu* jeu){
    Strategie* strat = (Strategie*)malloc(sizeof(Strategie));

    Joueur* moi = recupereInfoJoueurParID(jeu->joueurs,monID,jeu->nbJoueur);

    char** commands = initCommandes();    
    strat->moi = moi;
    strat->nbCommand = 0;
    strat->commands = commands;
    strat->jeu = jeu;

    return strat;
}
    //Pour l'instant, ajoute un bus a la premiere station
    //Au tout début, dans tous les cas il faut acheter un bus sinon game over
    //et on peut forcément acheter un bus au début 
void firstTurn(Strategie* s){
    addCommand(s,commande_ajouteBus(0));
}

void updateBusCanMove(Strategie* strat){

    Bus* mesBus = strat->moi->bus;
    int nbStation = strat->jeu->nbStation;
    
    for(int i = 0; i < strat->moi->nbBus ; i++){
        Station* s = getStationByIDStation(strat->jeu->stations,nbStation,mesBus[i].IDStationDest);
        if(busCanMove(mesBus[i],*s) == 1 )
            mesBus[i].canMove = 1;
    }
}


void moveBuses(Strategie* strat){
    Station* s;
    Bus* mesBus = strat->moi->bus;
    Station* stations = NULL;
    int nbStations = 0;

    for(int i = 0 ; i < strat->moi->nbBus ; i++){
        if(mesBus[i].canMove == 1){
            int nbPassenger = nbVoyageur(mesBus[i].voyageurs);
            if(nbPassenger != 0){
                stations = getStationsOfPassengers(strat->jeu->stations, 
                                        strat->jeu->nbStation, mesBus[i].voyageurs, nbPassenger);
                nbStations = nbPassenger;
            }
            else{
                nbStations = strat->jeu->nbStation;
                stations = getStationsNotEmpty(strat->jeu->stations, &nbStations);
            }
            if(nbStations != 0){
                s=getClosestStation(mesBus[i].position, stations, nbStations);
                mesBus[i].canMove = 0;
                addCommand(strat,commande_dirigerBus(mesBus[i].ID,s->ID));
            }
        }
    }
}

void buyImprovements(Strategie* s){

    if(peutAcheterBus(*(s->moi)) == 1) //Des qu'on peut on achete jusqu'a posséder 4 bus{}
        addCommand(s,commande_ajouteBus(0));
   
    if(s->moi->nbBus == MAX_NOMBRE_BUS && peutAugmenterSP(*(s->moi)) == 1) //Des qu'on a 4 bus, on ameliore la vitesse
        addCommand(s,commande_ameliorerSP());

    if(s->moi->SP == MAX_AUGMENTATION_SP && peutAugmenterCT(*(s->moi)) == 1)
       addCommand(s,commande_ameliorerCT());
}

void everyTurn(Strategie* s){
    
    buyImprovements(s);
    updateBusCanMove(s); //Check si les bus sont arrives a destination ou non puis met a jour les variables
    moveBuses(s);
    
    if(s->nbCommand == 0)
        addCommand(s,commande_pass());
}

void start(Jeu* jeu){

    Strategie* strat = initStructStrategie(jeu);

    if(jeu->tour == 0)
        firstTurn(strat);
    else
        everyTurn(strat);

    sendCommands(strat->commands,strat->nbCommand);
    freeStrategy(strat);
}