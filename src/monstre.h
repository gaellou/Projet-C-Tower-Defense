#ifndef __MONSTRE_H__
#define __MONSTRE_H__


#include "node.h"

typedef struct s_monstre{
    int x;
    int y;
    node * dest;
    node * oldDest;
    int vitesse;
    int vie;
    int direction; // orientation du sprite
    int idmonstre; //orde dans la vague
    int typemonstre;
    float resistTour1;
    float resistTour2;
    float resistTour3;
    float resistTour4;
    int go;
    struct s_monstre* next;
} monstre;
typedef monstre* l_monstre;

l_monstre ajoutermonstre(l_monstre liste, l_node listeNode, int idmonstre, int vie, int typemonstre, float resistTour1,float resistTour2,float resistTour3,float resistTour4);
l_monstre supprimermonstre(l_monstre liste, int idmonstre);
l_monstre supprimerAllmonstre(l_monstre liste);
void deplacemonstre (l_monstre liste, float timeVague, int vague, char** message, int * bouge, int * WinLose);
void Affichermonstre (l_monstre liste, int vague, int * bouge);
void DessinMonstre(l_monstre liste, int vague, int mouv);

#endif