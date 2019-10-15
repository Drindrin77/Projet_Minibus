#include "strategie.h"

void libereMemoireStrategie(Strategie* s){
    libereMemoireCommandes(s->commandes,s->tailleCommandes);
    free(s);
}

Strategie* initialiserStructStrategie(Jeu* jeu){
    Strategie* strat = (Strategie*)malloc(sizeof(Strategie));

    Joueur* moi = recupereInfoJoueurParID(jeu->joueurs,monID,jeu->nbJoueur);
    char** commandes = (char**)malloc(sizeof(char*)*NOMBRE_COMMANDES);
    
    strat->moi = moi;
    strat->tailleCommandes = 0;
    strat->commandes = commandes;
    strat->jeu = jeu;

    return strat;
}
void start(Jeu* jeu){

    Strategie* strat = initialiserStructStrategie(jeu);

    //Au tout début, dans tous les cas il faut acheter un bus sinon game over
    //et on peut forcément acheter un bus au début 
    //ajouteBus();
}