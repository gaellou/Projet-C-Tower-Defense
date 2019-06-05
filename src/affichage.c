#define M_PI 3.14159265358979323846

#include <stdlib.h>
#include <stdio.h>


#include <math.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_image.h>

#include <SDL/SDL_ttf.h>

#include "affichage.h"

static unsigned int WINDOW_WIDTH = 1000;
static unsigned int WINDOW_HEIGHT = 800;
static unsigned int PIXEL_WIDTH = 1000;
static unsigned int PIXEL_HEIGHT = 800;


static const unsigned int BIT_PER_PIXEL = 32;


/*--------------------------------------------------------------
                    Fonctions relatives à la fenêtre (faites en TP)
 --------------------------------------------------------------*/

void reshape() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0., PIXEL_WIDTH, -0., PIXEL_HEIGHT);
}

void setVideoMode() {
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE | SDL_INIT_TIMER)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        exit(EXIT_FAILURE);
    }
    reshape();
    glClear (GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND); //enable the blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //set the blend function
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapBuffers();
}

void afficherMouse(int xMove, int yMove, int PIXEL_HEIGHT){
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();
    glTranslatef(xMove, PIXEL_HEIGHT-yMove,1),
    glColor3ub(255, 255, 255);
    glBindTexture(GL_TEXTURE_2D, 12);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 0);
    glVertex2f(17, 0);
    glTexCoord2f(0, 0);
    glVertex2f(-12, 0);
    glTexCoord2f(0, 1);
    glVertex2f(-12,-30);
    glTexCoord2f(1, 1);
    glVertex2f(17, -30);
    glEnd();
    
}

void afficherMenuWin(int Winloose){
    if(Winloose == 1){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 7);
        glColor4f(1,1,1,1);
        glLoadIdentity();
        glBegin(GL_QUADS);
        glTexCoord2f(1, 0);
        glVertex2f(1000, 800);
        glTexCoord2f(0, 0);
        glVertex2f(0,800);
        glTexCoord2f(0, 1);
        glVertex2f(0, 0);
        glTexCoord2f(1, 1);
        glVertex2f(1000, 0);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);

    }
}
void afficherMenuLose(int  Winloose){
    if(Winloose == 2){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 8);
        glColor4f(1,1,1,1);
        glLoadIdentity();
        glBegin(GL_QUADS);
        glTexCoord2f(1, 0);
        glVertex2f(1000, 800);
        glTexCoord2f(0, 0);
        glVertex2f(0,800);
        glTexCoord2f(0, 1);
        glVertex2f(0, 0);
        glTexCoord2f(1, 1);
        glVertex2f(1000, 0);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);

    }
}
