#include <stdlib.h>
#include <stdio.h>

#include "bus.h"

void ajouterNouveauBus(Bus* buss, Bus b, int nbBus){

    buss[nbBus-1].ID = b.ID;
    buss[nbBus-1].nbVoiture = b.nbVoiture;
    buss[nbBus-1].IDStationDest = b.IDStationDest;
    buss[nbBus-1].nbVoiture = b.nbVoiture;
    buss[nbBus-1].X = b.X;
    buss[nbBus-1].Y = b.Y;

    // TODO: Si le nouveau bus a déjà des voyageurs ? le remplir ?
    //(*buss)[nbBus-1].voyageurs = (ListeVoyageur*)malloc(sizeof(ListeVoyageur));
}

void afficherListeBus(Bus* buss, int nbBus){
    for(int i = 0 ; i < nbBus ; i++){
        fprintf(stderr,"Buss n°%d",i);
        fprintf(stderr,"ID: %d", buss[i].ID);
    }
}
int contientBus(Bus* buss, int idBus, int nbBus){

    for(int i = 0 ; i < nbBus ; i++){
        if(buss[i].ID == idBus)
            return 1;
    }
    return 0;
}

Bus* obtenirBussContientIDVoyageur(Joueur* joueurs, int idVoyageur, int nbJoueur){
    for(int i = 0 ; i < nbJoueur ; i++){
        if( contientVoyageur(joueurs[i].bus->voyageurs, idVoyageur) == 1)
            return joueurs[i].bus;
    }
    return NULL;
}

//1 entier : nombre de bus en circulation
//6 entiers : info buss
void recupereDonneeBus(Jeu* jeu){

    int nbBus,idJoueur;
    scanf("%d", &nbBus);
    fprintf(stderr,"Nb de bus: %d \n",nbBus);

    Bus b;

    fprintf(stderr,"Debut liste bus: \n");
    //ID J X Y A S: bus, idJoueur le possedant, position X Y du bus, direction id Station, nombre de voiture
    for(int i = 0 ; i < nbBus ; i++){
        scanf("%d %d %d %d %d %d", &b.ID, &idJoueur, &b.X, &b.Y, &b.IDStationDest, &b.nbVoiture);
        fprintf(stderr,"Info bus n°%d : %d %d %d %d %d %d \n", i, b.ID, idJoueur, b.X, b.Y, b.IDStationDest, b.nbVoiture);

        Joueur* j = recupereInfoJoueurParID(jeu->joueurs, idJoueur, jeu->nbJoueur);
        
        //Si le joueur ne contient pas le bus, l'ajoute
        if( contientBus(j->bus, b.ID, j->nbBus) == 0 ){
            j->nbBus++;
            ajouterNouveauBus(j->bus, b, j->nbBus);
        }
    }
    fprintf(stderr,"Fin liste bus \n");
}