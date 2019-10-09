#include "joueur.h"
#include <stdio.h>
#include <stdlib.h>

Joueur* recupereInfoJoueurParID(Joueur* joueurs, int ID, int nbJoueur){
    for(int i = 0 ; i < nbJoueur ; i++){
        if(joueurs[i].ID == ID){
            return &joueurs[i];
        }
    }
    return NULL;
}

Bus* recupereBusJoueurParIDBus(Joueur* joueurs, int idBus, int nbJoueur){
    for(int i = 0 ; i < nbJoueur ; i++){
        if( contientBus(joueurs[i].bus, idBus, joueurs[i].nbBus) == 1)
            return joueurs[i].bus;
    }
    return NULL;
}

//Recupere les infos des joueurs
//5 entiers : ID joueur, son argent, nombre d'amélioration SB, SP et CT
void recupereDonneeJoueurs(Jeu* jeu){
    Joueur j ;

    for (int i = 0 ; i < jeu->nbJoueur ; i++){
        j = jeu->joueurs[i];
        scanf("%d %d %d %d %d %d", &j.ID, &j.argent, &j.SB, &j.SP, &j.CT, &j.victoire);
        fprintf(stderr, "Joueur n°%d: %d %d %d %d %d %d\n", i,j.ID, j.argent, j.SB, j.SP, j.CT, j.victoire);
    }
}
