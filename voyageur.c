#include "voyageur.h"
#include <stdlib.h>
#include <stdio.h>

//PRIVE

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

ListeVoyageur* creerVoyageur(ListeVoyageur* suivant, Voyageur* v){
    ListeVoyageur* retour = (ListeVoyageur*)malloc(sizeof(ListeVoyageur));
    retour->v.ID = v->ID;
    retour->v.IDS1 = v->IDS1;
    retour->v.IDS2 = v->IDS2;
    retour->suivant = suivant;
    return retour;
}

//PUBLIC

int contientVoyageur(ListeVoyageur* l, int idVoyageur){
    ListeVoyageur* tmp = l;
    while(tmp!=NULL){
        if(tmp->v.ID == idVoyageur)
            return 1;
        tmp=tmp->suivant;
    }
    return 0;
}

void afficherListeVoyageur(ListeVoyageur* listes){

    ListeVoyageur* tmp = listes;
    fprintf(stderr,"afficherlistevoyageur\n");
    while(tmp != NULL){
        fprintf(stderr,"ID voyageur: %d\n", tmp->v.ID);
        tmp=tmp->suivant;
    }
    
}
//Ajout d'un passager au debut de la liste chainee
ListeVoyageur* ajouterVoyageurDansListe(Voyageur* v, ListeVoyageur* voyageurs){

    return creerVoyageur(voyageurs, v);
}

ListeVoyageur* supprimerVoyageurDansListe(int idVoyageur, ListeVoyageur* voyageurs, int liberer){
    ListeVoyageur* tmp = voyageurs;
    ListeVoyageur* prev; 
    // Si le voyageur a supprimé est en tete de liste 
    if (tmp != NULL && tmp->v.ID == idVoyageur) 
    { 
        fprintf(stderr,"if\n");
        prev = tmp->suivant;   // Changed head 
        if(liberer==1)
            free(voyageurs);
        return prev;               // free old head 
    } 
    else{
        fprintf(stderr,"else\n");
        while (tmp != NULL && tmp->v.ID != idVoyageur) { 
            prev = tmp; 
            tmp = tmp->suivant; 
        } 
        // If key was not present in linked list 
        if (tmp == NULL) return NULL; 
        // Unlink the node from linked list 
        prev->suivant = tmp->suivant; 
        if(liberer==1)
            free(tmp);  // Free memory 
        return voyageurs;
    }
    
}
    //On supprime le voyageur de la liste d'attente et on l'ajoute
    //dans la liste de voyageur du bus du joueur concerné
void faireMonterVoyageurDansBus(Jeu* jeu,int idt, int idb){
        Voyageur* v2 =recupereInfoVoyageurParID(jeu->voyageursEnAttente,idt);
        jeu->voyageursEnAttente = supprimerVoyageurDansListe(idt,jeu->voyageursEnAttente,0);
        
        Bus* buss = recupereBusJoueurParIDBus(jeu->joueurs, idb, jeu->nbJoueur);
        buss->voyageurs = ajouterVoyageurDansListe(v2,buss->voyageurs);
}

void faireDescendreVoyageurDuBus(Jeu* jeu, int idt){
    Bus* buss = obtenirBussContientIDVoyageur(jeu->joueurs,idt,jeu->nbJoueur);
    fprintf(stderr,"%p\n",buss);
    if(buss!=NULL)
        buss->voyageurs=supprimerVoyageurDansListe(idt,buss->voyageurs,1);
}
void recupereDonneeVoyageur(Jeu* jeu){

    int nbNvVoyageur, nbVoyageurMonter, nbVoyageurDescendre; 

    //NT BT DT: nbr nouveaux voyageurs, nbr voyageurs montés dans un bus au tour précédent
    //nbr voyageurs quitté bus au tour précédent.
    scanf("%d %d %d", &nbNvVoyageur, &nbVoyageurMonter, &nbVoyageurDescendre);   
    fprintf(stderr,"Nouveau Voyageur: %d, NbMonter %d, NbDescendre: %d\n", nbNvVoyageur, nbVoyageurMonter, nbVoyageurDescendre);

    //IDT IDS1 IDS2 : ID NOUVEAU Passager, où le voyageur est apparu et où il se rend 
    Voyageur v;

    fprintf(stderr,"Debut liste nouveaux voyageurs\n");

    for(int i = 0 ; i < nbNvVoyageur ; i++){
        scanf("%d %d %d", &v.ID, &v.IDS1, &v.IDS2);
        fprintf(stderr," %d , id: %d, ids1: %d, ids2: %d\n", nbNvVoyageur, v.ID, v.IDS1, v.IDS2);
        jeu->voyageursEnAttente = ajouterVoyageurDansListe(&v,jeu->voyageursEnAttente);

    }
    fprintf(stderr,"Fin liste nouveaux voyageurs\n");

    //IDT IDB : ID voyageur, IDB Bus dans lequel le voyageur est monté au dernier tour

    fprintf(stderr,"Debut liste monter voyageurs\n");

    int idt, idb;
    for(int i = 0 ; i < nbVoyageurMonter ; i++){
        scanf("%d %d", &idt, &idb);
        fprintf(stderr,"id voyageur: %d , idbus: %d\n", idt, idb);  
        faireMonterVoyageurDansBus(jeu,idt,idb);
    }
    
    fprintf(stderr,"Fin liste monter voyageurs\n");

    fprintf(stderr,"Debut liste descendre voyageurs\n");

    //IDT Un numéro de voyageur IDT ayant quitté son bus au dernier tour.
    for(int i = 0 ; i < nbVoyageurDescendre ; i++){
        scanf("%d", &idt);
        fprintf(stderr,"idt %d \n", idt);
        faireDescendreVoyageurDuBus(jeu, idt);
    }
    fprintf(stderr,"fin liste descendre voyageurs\n");

    //afficherListeVoyageur(jeu->voyageursEnAttente);
    afficherListeVoyageur(jeu->joueurs[0].bus->voyageurs);

}
