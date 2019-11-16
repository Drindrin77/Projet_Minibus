#include <stdlib.h>
#include <stdio.h>

#include "bus.h"

void ajouterNouveauBus(Bus* buss, Bus b, int nbBus){
    buss[nbBus-1].ID = b.ID;
    buss[nbBus-1].nbVoiture = b.nbVoiture;
    buss[nbBus-1].IDStationDest = b.IDStationDest;
    buss[nbBus-1].position.X = b.position.X;
    buss[nbBus-1].position.Y = b.position.Y;
    buss[nbBus-1].peutChangerDest = 1;
}

void displayBuses(Bus* buss, int nbBus){
    for(int i = 0 ; i < nbBus ; i++){
        fprintf(stderr,"buss id : %d, iddest : %d\n" ,buss[i].ID,buss[i].IDStationDest);
    }
}

Bus* recupereBusJoueurParIDBus(Joueur* joueurs, int idBus, int nbJoueur){
    Joueur joueur;
    for(int i = 0 ; i < nbJoueur ; i++){
        joueur = joueurs[i];
        for(int j = 0 ; j < joueur.nbBus ; j++){
            if( joueur.bus[j].ID == idBus)
                return &(joueur.bus[j]);           
        }
    }
    return NULL;
}

void updateDataBus(Bus* bToUp, Bus b){
    bToUp->nbVoiture = b.nbVoiture;
    bToUp->position.X = b.position.X;
    bToUp->position.Y = b.position.Y;
    bToUp->IDStationDest = b.IDStationDest;
}

int contientBus(Bus* buss, int idBus, int nbBus){
    for(int i = 0 ; i < nbBus ; i++){
        if(buss[i].ID == idBus)
            return 1;
    }
    return 0;
}

int ceiling(int n){
    return (n + NB_VOYAGEUR_MAX_CHARGEMENT - 1) / NB_VOYAGEUR_MAX_CHARGEMENT;
}

int busPeutRepartir(Bus b, Station s){
    if(memePosition(b.position,s.position)==1){
        if( nbVoyageurVeutDescendre(s.ID,b.voyageurs) == 0){

            int nbVoyageurDansBus = nbVoyageur(b.voyageurs);
            //BUS PLEIN
            if(nbVoyageurDansBus == b.nbVoiture*5)
                return 1;

            int nbVoyageurStation = nbVoyageur(s.voyageursEnAttente);
            int nbTourPourCharger;
            int nbVoyageursARemplir = (b.nbVoiture*5) - nbVoyageurDansBus;

            if(nbVoyageurStation<nbVoyageursARemplir)
                nbTourPourCharger = ceiling(nbVoyageurStation);
            else
                nbTourPourCharger = ceiling(nbVoyageursARemplir);

            if(nbTourPourCharger == 0)
                return 1;
        }
    }
    return 0;
}

Bus* obtenirBussContientIDVoyageur(Joueur* joueurs, int idVoyageur, int nbJoueur){

    for(int i = 0 ; i < nbJoueur ; i++){
        for(int j = 0 ; j < joueurs[i].nbBus ; j++){
            Bus* bus = &(joueurs[i].bus[j]);
            if( contientVoyageur(bus->voyageurs, idVoyageur) == 1)
                return bus;
        }
    }
    return NULL;
}
Bus* getBusOfPlayerByIDBus(Joueur j, int idBus){
    for(int i = 0 ; i < j.nbBus ; i++){
        if(j.bus[i].ID == idBus)
            return &j.bus[i];
    }
    return NULL;
}

//1 entier : nombre de bus en circulation
//6 entiers : info buss
void recupereDonneeBus(Jeu* jeu){

    int nbBus,idJoueur;
    scanf("%d", &nbBus);

    Bus b;

    //ID J X Y A S: bus, idJoueur le possedant, position X Y du bus, direction id Station, nombre de voiture
    for(int i = 0 ; i < nbBus ; i++){
        scanf("%d %d %d %d %d %d", &b.ID, &idJoueur, &b.position.X, &b.position.Y, &b.IDStationDest, &b.nbVoiture);

        Joueur* j = recupereInfoJoueurParID(jeu->joueurs, idJoueur, jeu->nbJoueur);

        //Si le joueur ne contient pas le bus, l'ajoute
        if( contientBus(j->bus, b.ID, j->nbBus) == 0 ){
            j->nbBus++;
            ajouterNouveauBus(j->bus, b, j->nbBus);
        }else{
            Bus* bToUpdate = getBusOfPlayerByIDBus(*j,b.ID);
            updateDataBus(bToUpdate,b);
        }
    }
}