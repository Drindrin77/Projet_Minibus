#ifndef ACTION_HEADER
#define ACTION_HEADER

#define MAX_SIZE_COMMAND_NAME 20
#define NOMBRE_COMMANDES 7

#define PRIX_ACHETER_BUS 100
#define PRIX_AGRANDIR_BUS 50
#define PRIX_AUGMENTER_SB 100
#define PRIX_AUGMENTER_SP 200
#define PRIX_AUGMENTER_CT 100

#define MAX_AUGMENTATION_CT 5
#define MAX_AUGMENTATION_SP 2
#define MAX_AUGMENTATION_SB 2

#include "jeu.h"

typedef struct Joueur Joueur;
typedef struct ListeVoyageur ListeVoyageur;
typedef struct Jeu Jeu;


//GESTION MEMOIRE COMMANDES
void libereMemoireCommandes(char** commandes, int size);
void envoieCommande(char** commandes,int size);

// LISTE DES COMMANDES POSSIBLES SANS VERIFICATION
char* ajouteBus(int idStation);
char* dirigerBus(int idBus, int idStation);
char* augmenteTailleBus(int idBus);
char* ameliorerSB();
char* ameliorerSP();
char* ameliorerCT();
char* pass();

// LISTE DES CONDITIONS DES AMELIORATIONS

int peutAcheterBus(Joueur j);
int peutAgrandirBus(Joueur j, Bus bus);
int peutAugmenterSB(Joueur j);
int peutAugmenterSP(Joueur j);
int peutAugmenterCT(Joueur j);

#endif