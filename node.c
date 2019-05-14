#define M_PI 3.14159
#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include <SDL/SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <SDL_image/SDL_image.h>

#include <SDL_ttf/SDL_ttf.h>


#include "monster.h"
#include "tower.h"


/*AJOUTER NOEUD*/

l_node ajouterNode(l_node liste, int x, int y){
    node* nouvelElement = (node*)(malloc(sizeof(node)));
    if(nouvelElement == NULL){
        fprintf(stderr, "Erreur allocation : NOEUD\n");
        exit(EXIT_FAILURE);
    }
    nouvelElement->x = x;
    nouvelElement->y = y;
    nouvelElement->next = NULL;
    if(liste == NULL){
        return nouvelElement;
    }
    else{
        node* temp=liste;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = nouvelElement;
        return liste;
    }
}

/*AFFICHE LES VALEURS DU NOEUD*/

void afficherNodes(l_node liste){
    node *tmp = liste;
    while(tmp != NULL){
        printf("x : %d", tmp->x);
        printf("y : %d \n", tmp->y);
        tmp = tmp->next;
    }
}

/*SUPPRIME TOUT LES NOEUDS*/

l_node supprimerAllNode(l_node liste){
    node* tmp = liste;
    while(tmp!=NULL){
        tmp = tmp->next;
        free(tmp);
    }
    return NULL;
}