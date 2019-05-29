#ifndef __MONSTRE_H__
#define __MONSTRE_H__


#include "node.h"

typedef struct s_Monstre{
    int x;
    int y;
    node * dest;
    node * oldDest;
    int vitesse;
    int vie;
    int direction; // orientation du sprite (à venir si possible)
    int idmonstre; //orde dans la vague
    int typemonstre;
    float resistTour1;
    float resistTour2;
    float resistTour3;
    float resistTour4;
    int go;
    struct s_Monstre* next;
} Monstre;
typedef Monstre* l_Monstre;

l_Monstre ajoutermonstre(l_Monstre liste, l_node listeNode, int idmonstre, int vie, int typemonstre, float resistTour1,float resistTour2,float resistTour3,float resistTour4);
l_Monstre supprimermonstre(l_Monstre liste, int idmonstre);
l_Monstre supprimerAllmonstre(l_Monstre liste);
void deplacemonstre (l_Monstre liste, float timeVague, int vague, char** message, int * bouge, int * WinLose);
void Affichermonstre (l_Monstre liste, int vague, int * bouge);
void DessinMonstre(l_Monstre liste, int vague, int mouv);

#endif