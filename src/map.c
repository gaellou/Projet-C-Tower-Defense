#define M_PI 3.14159

#define MAXSZ 100
#define BFFSIZE 1024

#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_image.h>

#include <SDL/SDL_ttf.h> 

#include "map.h"
#include "node.h"


 

l_node addCoordNoeud(char* fileName) {
    char line[MAXSZ];
    int x, y;
    FILE *fIn;
    l_node ma_liste = NULL;
    int compteurLigneNoeud;

    //compteur j à utiliser pour boucler sur les valeurs des points formant un segment
    int i;
    //compteur à utiliser pour les lignes dans la boucle while.
    i = 0;
    //printf("nom du fichier ////////// %s", fileName);
    fIn = fopen (fileName, "r");
    // effectue le truc ligne par ligne.
    while (fgets (line, sizeof(line), fIn) != NULL) {
        i++;
        if(i>=8){
            //listing des 8 lignes qui permettent de créer des segments
            fscanf(fIn, "%d %d", &x,&y);
            printf("x : %d y : %d \n", x,y);
            ma_liste = ajouterNode(ma_liste, x, y);
            compteurLigneNoeud++;

        }//endif
    }//endWhile
    //printf("Nombre de ligne dans la fonction %d", compteurLigneNoeud);
    fclose (fIn);
    return ma_liste;
}

void DessinMap(void) {
    //map
    glLoadIdentity();
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glEnable(GL_TEXTURE_2D);
    glColor3ub(255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 0);
    glVertex2f(1000, 730);
    glTexCoord2f(0, 0);
    glVertex2f(0, 730);
    glTexCoord2f(0, 1);
    glVertex2f(0,0);
    glTexCoord2f(1, 1);
    glVertex2f(1000, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}