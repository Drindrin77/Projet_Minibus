#include "action.h"

void libereMemoireCommandes(char** commandes, int size){
    for(int i = size-1 ; i >= 0 ; i--){
        free(commandes[i]);
    }
    free(commandes);
}

void envoieCommande(char** commandes,int size){
    char* resultat = (char*)malloc(sizeof(char)*(size*MAX_SIZE_COMMAND_NAME));
    for(int i = 0 ; i < size ; i++){
        strcat(resultat,commandes[i]);
    }
    printf("%s\n",resultat);
    free(resultat);
}


char* ajouteBus(int idStation){
    char* commande = (char*)malloc(sizeof(char)*MAX_SIZE_COMMAND_NAME);
    snprintf(commande,MAX_SIZE_COMMAND_NAME,"BUS %d",idStation);
    return commande;
}

char* dirigerBus(int idBus, int idStation){
    char* commande = (char*)malloc(sizeof(char)*MAX_SIZE_COMMAND_NAME);
    snprintf(commande,MAX_SIZE_COMMAND_NAME,"DESTINATION %d %d",idBus,idStation);
    return commande;
}
char* augmenteTailleBus(int idBus){
    char* commande = (char*)malloc(sizeof(char)*MAX_SIZE_COMMAND_NAME);
    snprintf(commande,MAX_SIZE_COMMAND_NAME,"UPGRADE %d",idBus);
    return commande;
}
char* ameliorerSB(){
    char* commande = (char*)malloc(sizeof(char)*9);
    snprintf(commande,9,"UPDATESB");
    return commande;
}

char* ameliorerSP(){
    char* commande = (char*)malloc(sizeof(char)*9);
    snprintf(commande,9,"UPDATESP");
    return commande;
}
char* ameliorerCT(){
    char* commande = (char*)malloc(sizeof(char)*9);
    snprintf(commande,9,"UPDATECT");
    return commande;
}
char* pass(){
    char* commande = (char*)malloc(sizeof(char)*5);
    snprintf(commande,5,"PASS");
    return commande;
}
// LISTE DES CONDITIONS DES AMELIORATIONS

int peutAcheterBus(Joueur j){
    if(j.argent < PRIX_ACHETER_BUS || j.nbBus == 4);
        return 0;
    return 1;
}
 //si SB == 1, bus peut transporter 2 voitures max, si SB == 2, bus peut transporter 3 voitures max
int peutAgrandirBus(Joueur j, Bus bus){
    if(j.argent < PRIX_AGRANDIR_BUS || bus.nbVoiture == j.SB + 1)
        return 0;
    return 1;
}

int peutAugmenterSB(Joueur j){
    if(j.argent < PRIX_AUGMENTER_SB || j.SB > MAX_AUGMENTATION_SB) //SB peut etre ameliorer 2 fois max
        return 0;
    return 1;
}

int peutAugmenterSP(Joueur j){
    if(j.argent < PRIX_AUGMENTER_SP || j.SP > MAX_AUGMENTATION_SP)
        return 0;
    return 1;
}

int peutAugmenterCT(Joueur j){
    if(j.argent < PRIX_AUGMENTER_CT || j.CT > MAX_AUGMENTATION_CT)
        return 0;
    return 1;
}