#ifndef JOUEUR_HEADER
#define JOUEUR_HEADER

#include "jeu.h"
typedef struct Bus Bus;
typedef struct Jeu Jeu;

typedef struct Joueur{
    int ID;
    int SB;
    int SP;
    int CT;
    int argent;
    int nbBus;
    int victoire;
    Bus* bus;
}Joueur;

Joueur* recupereInfoJoueurParID(Joueur* joueurs, int ID, int nbJoueur);
void recupereDonneeJoueurs(Jeu* jeu);
Bus* recupereBusJoueurParIDBus(Joueur* joueurs, int idBus, int nbJoueur);

#endif