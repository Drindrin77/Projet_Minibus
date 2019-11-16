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
    while(tmp!=NULL){
        if(tmp->v.ID == ID)
            return &(tmp->v);        
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

Station* getStationsOfPassengers(Station* stations, int nbStation, ListeVoyageur* l, int nbPassenger){
    Station* stationsPassengers = (Station*)malloc(sizeof(Station)*nbPassenger);
    ListeVoyageur* tmp = l;
    int i = 0;
    while(tmp!=NULL){
        i++;
        Station* s = getStationByIDStation(stations,nbStation,tmp->v.IDS2);
        addStation(stationsPassengers,*s,i);
        tmp=tmp->suivant;
    }
    return stationsPassengers;
}

int nbVoyageur(ListeVoyageur* l){
    ListeVoyageur* tmp = l;
    int nb = 0;
    while(tmp!=NULL){
        tmp=tmp->suivant;
        nb++;
    }
    return nb;
}

int nbVoyageurVeutDescendre(int idStation, ListeVoyageur* l){
    ListeVoyageur* tmp = l;
    int nb = 0;
    while(tmp!=NULL){
        if(tmp->v.IDS2 == idStation)
            nb++;
        tmp=tmp->suivant;
    }
    return nb;
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
    Bus* buss = obtenirBussContientIDVoyageur(jeu->joueurs,idt,jeu->nbJoueur);
    if(buss!=NULL)
        buss->voyageurs=supprimerVoyageurDansListe(idt,buss->voyageurs,1);
}


//Traitement des nouveaux voyageurs, on les ajoute dans la liste des voyageurs du station où ils
//sont apparus
void nouveauxVoyageurs(Jeu* jeu){
    Voyageur v;
    scanf("%d %d %d", &v.ID, &v.IDS1, &v.IDS2);

    Station* s = getStationByIDStation(jeu->stations,jeu->nbStation, v.IDS1);
    s->voyageursEnAttente = ajouterVoyageurDansListe(&v,s->voyageursEnAttente);
}


void recupereDonneeVoyageur(Jeu* jeu){

    int nbNvVoyageur, nbVoyageurMonter, nbVoyageurDescendre; 
    scanf("%d %d %d", &nbNvVoyageur, &nbVoyageurMonter, &nbVoyageurDescendre);   

    for(int i = 0 ; i < nbNvVoyageur ; i++)
        nouveauxVoyageurs(jeu);
    
    for(int i = 0 ; i < nbVoyageurMonter ; i++)
        faireMonterVoyageurDansBus(jeu);
    
    for(int i = 0 ; i < nbVoyageurDescendre ; i++)
        faireDescendreVoyageurDuBus(jeu);
}
