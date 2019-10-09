#ifndef BUS_HEADER
#define BUS_HEADER

#include "jeu.h"

typedef struct Joueur Joueur;
typedef struct ListeVoyageur ListeVoyageur;
typedef struct Jeu Jeu;


typedef struct Bus{
    int ID;
    int X;
    int Y;
    int IDStationDest;
    int capacite;
    int nbVoiture;
    ListeVoyageur* voyageurs;
}Bus;



void ajouterNouveauBus(Bus** buss, Bus b, int nbBus);
int contientBus(Bus* buss, int idBus, int nbBus);
void recupereDonneeBus(Jeu* jeu);
Bus* obtenirBussContientIDVoyageur(Joueur* joueurs, int idVoyageur, int nbJoueur);

#endif