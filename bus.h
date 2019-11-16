#ifndef BUS_HEADER
#define BUS_HEADER

#include "jeu.h"
#include "position.h"

#define NB_VOYAGEUR_MAX_CHARGEMENT 5

typedef struct Joueur Joueur;
typedef struct ListeVoyageur ListeVoyageur;
typedef struct Jeu Jeu;
typedef struct Position Position;
typedef struct Station Station;



typedef struct Bus{
    int ID;
    Position position;
    int IDStationDest;
    int nbVoiture; // 1 voiture = 5 voyageurs, 2 voiture = 10 ...
    int peutChangerDest;
    ListeVoyageur* voyageurs;
}Bus;


void ajouterNouveauBus(Bus* buss, Bus b, int nbBus);
int contientBus(Bus* buss, int idBus, int nbBus);
void recupereDonneeBus(Jeu* jeu);
Bus* obtenirBussContientIDVoyageur(Joueur* joueurs, int idVoyageur, int nbJoueur);
void displayBuses(Bus* buss, int nbBus);
int busPeutRepartir(Bus b, Station s);
Bus* recupereBusJoueurParIDBus(Joueur* joueurs, int idBus, int nbJoueur);
#endif