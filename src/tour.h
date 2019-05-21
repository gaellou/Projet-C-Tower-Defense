#ifndef __TOUR_H__
#define __TOUR_H__


#include "monstre.h"

typedef struct s_Tour{
    int x; //position
    int y;
    int rayon;
    int cost;
    int type;
    int puissance;
    float cadence;
    int active;
    float timeCrea;
    float timeConst;
    float timeDernierTir;
    struct s_Tour* next;
} Tour;
typedef Tour* l_Tour;

l_Tour ajouterTour(l_Tour liste, int* coins, int x, int y,int type, char** message);
l_Tour supprimerAllTour(l_Tour liste);
l_Tour selectTour(l_Tour liste, int x, int y, char** message);
void glisserTour(int x, int y, int type);
l_Tour supprimerTour(l_Tour liste, l_Tour aSuppr);
void afficherTour(l_Tour liste, int ray, l_Tour TourSelected);
void gestionTour(l_Tour listeTour, l_monstre listemonstre);

#endif
