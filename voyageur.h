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

void ajouterVoyageurDansListe(Voyageur p, ListeVoyageur* passagers);
void supprimerVoyageurDansListe(int idVoyageur, ListeVoyageur* voyageurs);
int contientVoyageur(ListeVoyageur* l, int idVoyageur);
void recupereDonneeVoyageur(Jeu* jeu);

#endif
