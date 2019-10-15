#include "voyageur.h"
#include <stdlib.h>
#include <stdio.h>

//PRIVE

ListeVoyageur* creerVoyageur(ListeVoyageur* suivant, Voyageur* v){
    ListeVoyageur* retour = (ListeVoyageur*)malloc(sizeof(ListeVoyageur));
    retour->v.ID = v->ID;
    retour->v.IDS1 = v->IDS1;
    retour->v.IDS2 = v->IDS2;
    retour->suivant = suivant;
    return retour;
}

//PUBLIC

Voyageur* recupereInfoVoyageurParID(ListeVoyageur* voyageurs, int ID){

    ListeVoyageur* tmp = voyageurs;
    if(tmp==NULL)
        return NULL;

    if(tmp->v.ID == ID)
        return &(tmp->v);
    
    while(tmp!=NULL){
        if(tmp->v.ID == ID){
            return &(tmp->v);
        }
        tmp=tmp->suivant;
    }
    return NULL;
}

int contientVoyageur(ListeVoyageur* l, int idVoyageur){
    ListeVoyageur* tmp = l;
    while(tmp!=NULL){
        if(tmp->v.ID == idVoyageur)
            return 1;
        tmp=tmp->suivant;
    }
    return 0;
}

//Fonction qui permet d'afficher l'id de tous les voyageurs de la liste
void afficherListeVoyageur(ListeVoyageur* listes){
    ListeVoyageur* tmp = listes;
    while(tmp != NULL){
        fprintf(stderr,"ID voyageur: %d\n", tmp->v.ID);
        tmp=tmp->suivant;
    }
}

//Ajout d'un passager au debut de la liste chainee
ListeVoyageur* ajouterVoyageurDansListe(Voyageur* v, ListeVoyageur* voyageurs){
    return creerVoyageur(voyageurs, v);
}

//Supression du voyageur de la liste donnée en parametre. 
//On indique dans l'entier liberer si on veut supprimer le voyageur du jeu  
//ou juste l'enlever de la liste
ListeVoyageur* supprimerVoyageurDansListe(int idVoyageur, ListeVoyageur* voyageurs, int liberer){
    ListeVoyageur* tmp = voyageurs;
    ListeVoyageur* prev; 
    // Si le voyageur a supprimé est en tete de liste 
    if (tmp != NULL && tmp->v.ID == idVoyageur) 
    { 
        prev = tmp->suivant;   // Changed head 
        if(liberer==1)
            free(voyageurs);
        return prev;               // free old head 
    } 
    else{
        while (tmp != NULL && tmp->v.ID != idVoyageur) { 
            prev = tmp; 
            tmp = tmp->suivant; 
        } 
        // Si le voyageur n'était pas dans la liste
        if (tmp == NULL) return NULL; 
        
        prev->suivant = tmp->suivant; 
        if(liberer==1)
            free(tmp);  // Free memory 

        return voyageurs;
    }
    
}
//On supprime le voyageur de la liste d'attente et on l'ajoute
//dans la liste de voyageur du bus du joueur concerné
void faireMonterVoyageurDansBus(Jeu* jeu){
    int idt, idb;
    scanf("%d %d", &idt, &idb);
    fprintf(stderr,"id voyageur: %d , idbus: %d\n", idt, idb);  
    Station* s = recupereStationParIdVoyageur(jeu->stations,jeu->nbStation,idt);
    Voyageur* v2 = recupereInfoVoyageurParID(s->voyageursEnAttente,idt);
    s->voyageursEnAttente = supprimerVoyageurDansListe(idt,s->voyageursEnAttente,0);
    
    Bus* buss = recupereBusJoueurParIDBus(jeu->joueurs, idb, jeu->nbJoueur);
    buss->voyageurs = ajouterVoyageurDansListe(v2,buss->voyageurs);
}
//On recherche le bus qui contient le voyageur qui descend.
//On free le voyageur pour le faire disparaitre du jeu
void faireDescendreVoyageurDuBus(Jeu* jeu){
    int idt;
    scanf("%d", &idt);
    fprintf(stderr,"idt %d \n", idt);
    Bus* buss = obtenirBussContientIDVoyageur(jeu->joueurs,idt,jeu->nbJoueur);
    if(buss!=NULL)
        buss->voyageurs=supprimerVoyageurDansListe(idt,buss->voyageurs,1);
}
//Traitement des nouveaux voyageurs, on les ajoutes dans la liste des voyageurs du station où ils
//sont apparus
void nouveauxVoyageurs(Jeu* jeu){
    Voyageur v;

    scanf("%d %d %d", &v.ID, &v.IDS1, &v.IDS2);
    fprintf(stderr,"id: %d, ids1: %d, ids2: %d\n", v.ID, v.IDS1, v.IDS2);

    Station* s = recupereStationParIdStation(jeu->stations,jeu->nbStation, v.IDS1);
    s->voyageursEnAttente = ajouterVoyageurDansListe(&v,s->voyageursEnAttente);
}
void recupereDonneeVoyageur(Jeu* jeu){

    int nbNvVoyageur, nbVoyageurMonter, nbVoyageurDescendre; 

    scanf("%d %d %d", &nbNvVoyageur, &nbVoyageurMonter, &nbVoyageurDescendre);   
    fprintf(stderr,"Nouveau Voyageur: %d, NbMonter %d, NbDescendre: %d\n", nbNvVoyageur, nbVoyageurMonter, nbVoyageurDescendre);

    fprintf(stderr,"Debut liste nouveaux voyageurs\n");
    for(int i = 0 ; i < nbNvVoyageur ; i++)
        nouveauxVoyageurs(jeu);
    
    fprintf(stderr,"Debut liste monter voyageurs\n");
    for(int i = 0 ; i < nbVoyageurMonter ; i++)
        faireMonterVoyageurDansBus(jeu);
    
    fprintf(stderr,"Debut liste descendre voyageurs\n");
    for(int i = 0 ; i < nbVoyageurDescendre ; i++)
        faireDescendreVoyageurDuBus(jeu);
    
}
