#include "strategie.h"

void libereMemoireStrategie(Strategie* s){
    libereMemoireCommandes(s->commandes,s->nbCommandes);
    free(s);
}

Strategie* initialiserStructStrategie(Jeu* jeu){
    Strategie* strat = (Strategie*)malloc(sizeof(Strategie));

    Joueur* moi = recupereInfoJoueurParID(jeu->joueurs,monID,jeu->nbJoueur);

    char** commandes = initCommandes();    
    strat->moi = moi;
    strat->nbCommandes = 0;
    strat->commandes = commandes;
    strat->jeu = jeu;

    return strat;
}

void premierTourStrat(Strategie* s){
    //Pour l'instant, ajoute un bus a la premiere station
    //Au tout début, dans tous les cas il faut acheter un bus sinon game over
    //et on peut forcément acheter un bus au début 
    ajouterCommande(s,commande_ajouteBus(0));
}


void updateBusStationTour(Strategie* strat){

    Bus* mesBus = strat->moi->bus;
    int nbStation = strat->jeu->nbStation;
    
    for(int i = 0; i < strat->moi->nbBus ; i++){
        Station* s = getStationByIDStation(strat->jeu->stations,nbStation,mesBus[i].IDStationDest);
        if(busPeutRepartir(mesBus[i],*s) == 1 )
            mesBus[i].peutChangerDest = 1;
    }
}


void faisAllerStationMoinLoinPourChaqueBus(Strategie* strat){
    Station* s;
    Bus* mesBus = strat->moi->bus;
    Station* stations = NULL;
    int nbStations = 0;

    for(int i = 0 ; i < strat->moi->nbBus ; i++){
        if(mesBus[i].peutChangerDest == 1){
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
                mesBus[i].peutChangerDest = 0;
                ajouterCommande(strat,commande_dirigerBus(mesBus[i].ID,s->ID));
            }
        }
    }
}

void chaqueTourStrat(Strategie* s){
    if(peutAcheterBus(*(s->moi)) == 1) //Des qu'on peut on achete jusqu'a posséder 4 bus{}
        ajouterCommande(s,commande_ajouteBus(0));
   
    if(s->moi->nbBus == MAX_NOMBRE_BUS && peutAugmenterSP(*(s->moi)) == 1) //Des qu'on a 4 bus, on ameliore la vitesse
        ajouterCommande(s,commande_ameliorerSP());


    //TEST AMELIORATION SP
   // if(s->moi->SP == MAX_AUGMENTATION_SP && peutAugmenterCT(*(s->moi)) == 1)
     //   ajouterCommande(s,commande_ameliorerCT());

    updateBusStationTour(s); //Check si les bus sont arrives a destination ou non puis met a jour les variables
    faisAllerStationMoinLoinPourChaqueBus(s);
    
    if(s->nbCommandes == 0)
        ajouterCommande(s,commande_pass());
}

void start(Jeu* jeu){

    Strategie* strat = initialiserStructStrategie(jeu);

    if(jeu->tour == 0)
        premierTourStrat(strat);
    else
        chaqueTourStrat(strat);

    envoieCommande(strat->commandes,strat->nbCommandes);
    libereMemoireStrategie(strat);
}