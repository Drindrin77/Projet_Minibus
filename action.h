#ifndef ACTION_HEADER
#define ACTION_HEADER

#define MAX_SIZE_COMMAND_NAME 20
#define MAX_SIZE_COMMANDS 20

#define PRIX_ACHETER_BUS 100
#define PRIX_AGRANDIR_BUS 50
#define PRIX_AUGMENTER_SB 100
#define PRIX_AUGMENTER_SP 200
#define PRIX_AUGMENTER_CT 100

#define MAX_AUGMENTATION_CT 5
#define MAX_AUGMENTATION_SP 2
#define MAX_AUGMENTATION_SB 2
#define MAX_NOMBRE_BUS 4

#include "jeu.h"
#include "string.h"

typedef struct Joueur Joueur;
typedef struct ListeVoyageur ListeVoyageur;
typedef struct Jeu Jeu;
typedef struct Strategie Strategie;

//GESTION MEMOIRE COMMANDES
void libereMemoireCommandes(char** commandes, int size);
void envoieCommande(char** commandes, int nbCommande);
char** initCommandes();
void ajouterCommande(Strategie* strat, char* c);

// LISTE DES COMMANDES POSSIBLES SANS VERIFICATION
char* commande_ajouteBus(int idStation);
char* commande_dirigerBus(int idBus, int idStation);
char* commande_augmenteTailleBus(int idBus);
char* commande_ameliorerSB();
char* commande_ameliorerSP();
char* commande_ameliorerCT();
char* commande_pass();

// LISTE DES CONDITIONS DES AMELIORATIONS

int peutAcheterBus(Joueur j);
int peutAgrandirBus(Joueur j, Bus bus);
int peutAugmenterSB(Joueur j);
int peutAugmenterSP(Joueur j);
int peutAugmenterCT(Joueur j);

#endif