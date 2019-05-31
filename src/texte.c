#define M_PI 3.14159

#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_image.h>

#include <SDL/SDL_ttf.h> 

#include "monstre.h"
#include "tour.h"
#include "texture.h"
#include "texte.h"


//affichage message erreur
void afficheMessageErreur(){
	glLoadIdentity();
	glColor4f(0,0,0,0.5);
	glBegin(GL_QUADS);
	glVertex2f(1000,715);
	glVertex2f(0,715);
	glVertex2f(0,693);
	glVertex2f(1000,693);
	glEnd();
	glColor4f(1,1,1,1);

}

//affichage argent
GLuint* afficheCoins(GLuint *textureId, int coins){

    char valeur[25] = "Coins : ";
    sprintf(valeur+8, "%d", coins);

    TTF_Font *police = NULL;
    SDL_Surface *texte = NULL;
    SDL_Color couleurBlanche = {255, 255, 255};
    /* Chargement de la police */
    police = TTF_OpenFont("images/police/hoog0656.ttf", 20);

    // Bind the texture object
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, textureId[10]);
    // Set the texture's stretching properties
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glLoadIdentity();
    glTranslatef(500,680,1);
    /* Écriture du texte  */
    texte = TTF_RenderText_Blended(police, valeur, couleurBlanche);

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texte->w, texte->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texte->pixels );
    glBegin(GL_QUADS);
    glColor3ub(255,255,255);
    glTexCoord2f(1, 0);
    glVertex2f(0+texte->w, 80+texte->h);
    glTexCoord2f(0, 0);
    glVertex2f(0, 80+texte->h);
    glTexCoord2f(0, 1);
    glVertex2f(0,80);
    glTexCoord2f(1, 1);
    glVertex2f(0+texte->w, 80);
    glEnd();

    glBindTexture( GL_TEXTURE_2D, 0 );
    glDisable(GL_TEXTURE_2D);
    TTF_CloseFont(police);
    SDL_FreeSurface(texte);

    return textureId;
}

//affichage nombre de vague

GLuint* afficheVagues(GLuint *textureId, int vague){

    char valeur[25] = "Vague : ";
    sprintf(valeur+8, "%d", vague);

    TTF_Font *police = NULL;
    SDL_Surface *texte = NULL;
    SDL_Color couleurBlanche = {255, 255, 255};
    /* Chargement de la police */
    police = TTF_OpenFont("images/police/hoog0656.ttf", 20);


    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, textureId[10]);
    // Set the texture's stretching properties
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glLoadIdentity();
    glTranslatef(350,680,1);
    //////////////
    /////VAGUE////
    //////////////
    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    texte = TTF_RenderText_Blended(police, valeur, couleurBlanche);
    // Edit the texture object's image data using the information SDL_Surface gives us
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texte->w, texte->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texte->pixels );
    glBegin(GL_QUADS);
    glColor3ub(255,255,255);
    glTexCoord2f(1, 0);
    glVertex2f(0+texte->w, 80+texte->h);
    glTexCoord2f(0, 0);
    glVertex2f(0, 80+texte->h);
    glTexCoord2f(0, 1);
    glVertex2f(0,80);
    glTexCoord2f(1, 1);
    glVertex2f(0+texte->w, 80);
    glEnd();

    glBindTexture( GL_TEXTURE_2D, 0 );
    glDisable(GL_TEXTURE_2D);
    TTF_CloseFont(police);
    SDL_FreeSurface(texte);

    return textureId;
}

//affichage de texte

GLuint* afficheTexte(GLuint *textureId, int x, int y, char * Texte, int r, int g, int b, int size){
    TTF_Font *police = NULL;
    SDL_Surface *texte = NULL;
    SDL_Color couleur = {r, g, b};
    /* Chargement de la police */
    police = TTF_OpenFont("images/police/hoog0656.ttf", size);

    // Bind the texture object
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, textureId[10]);
    // Set the texture's stretching properties
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glLoadIdentity();
    glTranslatef(x,y,1);

    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    texte = TTF_RenderText_Blended(police, Texte, couleur);
    // Edit the texture object's image data using the information SDL_Surface gives us
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texte->w, texte->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texte->pixels );
    glBegin(GL_QUADS);
    glTexCoord2f(1, 0);
    glVertex2f(0+texte->w, 80+texte->h);
    glTexCoord2f(0, 0);
    glVertex2f(0, 80+texte->h);
    glTexCoord2f(0, 1);
    glVertex2f(0,80);
    glTexCoord2f(1, 1);
    glVertex2f(0+texte->w, 80);
    glEnd();

    glBindTexture( GL_TEXTURE_2D, 0 );
    glDisable(GL_TEXTURE_2D);
    TTF_CloseFont(police);
    SDL_FreeSurface(texte);

    return textureId;
}