#ifndef STRATEGIE_HEADER
#define STRATEGIE_HEADER

#include "jeu.h"
#include "action.h"

typedef struct Joueur Joueur;
typedef struct Jeu Jeu;

//La structure va contenir tous les données du jeu et toutes les commandes.
typedef struct Strategie{
    Jeu* jeu;
    int nbCommandes;
    char** commandes;
    Joueur* moi;
}Strategie;

void start(Jeu* jeu);

#endif