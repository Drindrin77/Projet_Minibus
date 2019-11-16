#include "action.h"
#include <string.h>

void freeCommands(char** commandes, int size){
    for(int i = size-1 ; i >= 0 ; i--){
        free(commandes[i]);
    }
    free(commandes);
}
char** initCommandes(){
    char** commandes = (char**)malloc(sizeof(char*)*MAX_SIZE_COMMANDS);
    return commandes;
}

void addCommand(Strategie* strat, char* c){
    strat->commands[strat->nbCommand] = (char*)malloc(sizeof(char));
    strcpy(strat->commands[strat->nbCommand], c);
    strat->nbCommand++;
}

void sendCommands(char** commandes, int nbCommande){
    char* resultat = (char*)malloc(sizeof(char)*(nbCommande*MAX_SIZE_COMMAND_NAME));
    if(nbCommande > 0){
        strcpy(resultat,commandes[0]);
        for(int i = 1 ; i < nbCommande ; i++){
            strcat(resultat,";");
            strcat(resultat,commandes[i]);
        }
        printf("%s\n",resultat);
        free(resultat);
    }
}

char* commande_ajouteBus(int idStation){
    char* commande = (char*)malloc(sizeof(char)*MAX_SIZE_COMMAND_NAME);
    snprintf(commande,MAX_SIZE_COMMAND_NAME,"BUS %d",idStation);
    return commande;
}

char* commande_dirigerBus(int idBus, int idStation){
    char* commande = (char*)malloc(sizeof(char)*MAX_SIZE_COMMAND_NAME);
    snprintf(commande,MAX_SIZE_COMMAND_NAME,"DESTINATION %d %d",idBus,idStation);
    return commande;
}
char* commande_augmenteTailleBus(int idBus){
    char* commande = (char*)malloc(sizeof(char)*MAX_SIZE_COMMAND_NAME);
    snprintf(commande,MAX_SIZE_COMMAND_NAME,"UPGRADE %d",idBus);
    return commande;
}
char* commande_ameliorerSB(){
    char* commande = (char*)malloc(sizeof(char)*9);
    snprintf(commande,9,"UPDATESB");
    return commande;
}

char* commande_ameliorerSP(){
    char* commande = (char*)malloc(sizeof(char)*9);
    snprintf(commande,9,"UPDATESP");
    return commande;
}
char* commande_ameliorerCT(){
    char* commande = (char*)malloc(sizeof(char)*9);
    snprintf(commande,9,"UPDATECT");
    return commande;
}
char* commande_pass(){
    char* commande = (char*)malloc(sizeof(char)*5);
    snprintf(commande,5,"PASS");
    return commande;
}
// LISTE DES CONDITIONS DES AMELIORATIONS

int peutAcheterBus(Joueur j){
    if(j.argent < PRIX_ACHETER_BUS || j.nbBus == MAX_NOMBRE_BUS)
        return 0;
    return 1;
}
int peutAgrandirBus(Joueur j, Bus bus){
    if(j.argent < PRIX_AGRANDIR_BUS || bus.nbVoiture == j.SB + 1)
        return 0;
    return 1;
}

int peutAugmenterSB(Joueur j){
    if(j.argent < PRIX_AUGMENTER_SB || j.SB == MAX_AUGMENTATION_SB) //SB peut etre ameliorer 2 fois max
        return 0;
    return 1;
}

int peutAugmenterSP(Joueur j){
    if(j.argent < PRIX_AUGMENTER_SP || j.SP == MAX_AUGMENTATION_SP)
        return 0;
    return 1;
}

int peutAugmenterCT(Joueur j){
    if(j.argent < PRIX_AUGMENTER_CT || j.CT == MAX_AUGMENTATION_CT)
        return 0;
    return 1;
}