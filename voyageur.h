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

ListeVoyageur* ajouterVoyageurDansListe(Voyageur* p, ListeVoyageur* passagers);
ListeVoyageur* supprimerVoyageurDansListe(int idVoyageur, ListeVoyageur* voyageurs,int liberer);
int contientVoyageur(ListeVoyageur* l, int idVoyageur);
Voyageur* recupereInfoVoyageurParID(ListeVoyageur* voyageurs, int ID);
void recupereDonneeVoyageur(Jeu* jeu);
void afficherListeVoyageur(ListeVoyageur* listes);

#endif
