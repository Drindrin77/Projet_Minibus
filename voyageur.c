#include "voyageur.h"
#include <stdlib.h>
#include <stdio.h>

//PRIVE

Voyageur* recupereInfoVoyageurParID(ListeVoyageur* voyageurs, int ID){
    ListeVoyageur* tmp = voyageurs;
    if(tmp==NULL)
        fprintf(stderr,"VOYAGEURS ACTUELLEMENT NULL");
    while(tmp->suivant!=NULL){
        if(tmp->v.ID == ID)
            return &tmp->v;
    }
    return NULL;
}

ListeVoyageur* creerVoyageur(ListeVoyageur* suivant, Voyageur v){
    ListeVoyageur* retour = (ListeVoyageur*)malloc(sizeof(ListeVoyageur));
    retour->v.ID = v.ID;
    retour->v.IDS1 = v.IDS1;
    retour->v.IDS2 = v.IDS2;
    retour->suivant = suivant;
    return retour;
}

//PUBLIC

int contientVoyageur(ListeVoyageur* l, int idVoyageur){
    ListeVoyageur* tmp = l;
    while(tmp->suivant!=NULL){
        if(tmp->v.ID == idVoyageur)
            return 1;
    }
    return 0;
}
//Ajout d'un passager au debut de la liste chainee
void ajouterVoyageurDansListe(Voyageur v, ListeVoyageur* voyageurs){
    //Si pas de passager
    if(voyageurs==NULL){
        fprintf(stderr,"VOYAGEURS NULL");
        ListeVoyageur* nouveau = creerVoyageur(NULL, v);

        voyageurs = nouveau;
        fprintf(stderr,"AZE: %d = ",voyageurs->v.ID);

    }
    //Sinon ajout en debut de liste
    else{
        ListeVoyageur* nouveau = creerVoyageur(voyageurs, v);
        voyageurs = nouveau;
    }
}

void supprimerVoyageurDansListe(int idVoyageur, ListeVoyageur* voyageurs){
    ListeVoyageur* tmp = voyageurs;
    if(voyageurs == NULL) return;

    if(tmp->v.ID == idVoyageur){
        voyageurs = voyageurs->suivant;
        free(tmp);
    }
    else{
            int trouve=0;
        
        while(tmp->suivant != NULL && trouve==0){
            if(tmp->suivant->v.ID == idVoyageur){
                ListeVoyageur* tmp2 = tmp->suivant;
                tmp->suivant= tmp2->suivant;
                free(tmp2);
                trouve=1;
            }
        }
    }
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
        ajouterVoyageurDansListe(v,jeu->voyageursEnAttente);
    }
    fprintf(stderr,"Fin liste nouveaux voyageurs\n");

    //IDT IDB : ID voyageur, IDB Bus dans lequel le voyageur est monté au dernier tour
    //On supprime le voyageur de la liste d'attente et on l'ajoute
    //dans la liste de voyageur du bus du joueur concerné
    fprintf(stderr,"Debut liste monter voyageurs\n");

    int idt, idb;
    for(int i = 0 ; i < nbVoyageurMonter ; i++){
        scanf("%d %d", &idt, &idb);
        fprintf(stderr,"%d, id voyageur: %d , idbus: %d\n", nbVoyageurMonter, idt, idb);

        // Voyageur* v2 =recupereInfoVoyageurParID(jeu->voyageursEnAttente,idt);
        //         fprintf(stderr,"TEst");

        // supprimerVoyageurDansListe(idt,jeu->voyageursEnAttente);
        
        // Bus* buss = recupereBusJoueurParIDBus(jeu->joueurs, idb, jeu->nbJoueur);
        // ajouterVoyageurDansListe(*v2,buss->voyageurs);

    }
    fprintf(stderr,"Fin liste monter voyageurs\n");

    fprintf(stderr,"Debut liste descendre voyageurs\n");

    //IDT Un numéro de voyageur IDT ayant quitté son bus au dernier tour.
    for(int i = 0 ; i < nbVoyageurDescendre ; i++){
        scanf("%d", &idt);
        fprintf(stderr,"%d , idt %d \n", nbVoyageurDescendre, idt);

        // //TODO
        // Bus* buss = obtenirBussContientIDVoyageur(jeu->joueurs,idt,jeu->nbJoueur);
        // supprimerVoyageurDansListe(idt,buss->voyageurs);
    }
    fprintf(stderr,"fin liste descendre voyageurs\n");

}
