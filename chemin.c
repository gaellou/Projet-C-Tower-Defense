#define M_PI 3.14159

#include <stdlib.h>
#include <stdio.h>


#include <math.h>
#include <SDL/SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <SDL_image/SDL_image.h>
#include <SDL_ttf/SDL_ttf.h> /*bibliothèque texte*/


#include "node.h"
#include "chemin.h"

/*AFFICHAGE DU CHEMIN*/

void chemin(l_node liste, int r, int g, int b, int ir,int ig, int ib, int Or,int og, int ob) {
    int tmpX = liste->x;
    int tmpY = liste->y;

    glColor3ub(r, g, b);
    glBegin(GL_LINE_STRIP);
    while (liste->next!=NULL) {
        glVertex3f(liste->x, liste->y, 0.0f);
        liste=liste->next;
    }
    glEnd();
    //entrée
    glColor3ub(ir, ig, ib);
    glBegin(GL_POINTS);
    	glVertex3f(tmpX, tmpY, 0.0f);
    glEnd();

    //sortie
    glColor3ub(Or, og, ob);
    glBegin(GL_POINTS);
    	glVertex3f(liste->x, liste->y, 0.0f);
    glEnd();
}