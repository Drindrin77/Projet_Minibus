#ifndef VOYAGEUR_HEADER
#define VOYAGEUR_HEADER

#include "jeu.h"

typedef struct Voyageur{
    int ID;
    int IDS1;
    int IDS2;
}Voyageur;

typedef struct ListeVoyageur{
    Voyageur v;
    struct ListeVoyageur* suivant;
}ListeVoyageur;

typedef struct Station Station;

ListeVoyageur* ajouterVoyageurDansListe(Voyageur* p, ListeVoyageur* passagers);
ListeVoyageur* supprimerVoyageurDansListe(int idVoyageur, ListeVoyageur* voyageurs,int liberer);
int contientVoyageur(ListeVoyageur* l, int idVoyageur);
Voyageur* recupereInfoVoyageurParID(ListeVoyageur* voyageurs, int ID);
void recupereDonneeVoyageur(Jeu* jeu);
void afficherListeVoyageur(ListeVoyageur* listes);
int nbVoyageur(ListeVoyageur* l);
int nbVoyageurVeutDescendre(int idStation, ListeVoyageur* v);
Station* getStationsOfPassengers(Station* stations, int nbStation, ListeVoyageur* l, int nbPassenger);
#endif
