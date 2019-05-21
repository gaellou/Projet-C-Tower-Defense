#define M_PI 3.14159

#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include <SDL/SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <SDL_image/SDL_image.h>

#include <SDL_ttf/SDL_ttf.h> /*bibliothèque texte*/

#include "monstre.h"
#include "tour.h"



/*AJOUTER TOUR*/

l_tower ajouterTour(l_Tour liste, int* coins, int x, int y,int type, char** message){
    int error = 0;
    int ray;
    int puissance;
    float cadence;
    int cost;

    //en fonction du type de Tour
    switch(type) {
        case 1: //rouge
            ray = 200;
            puissance = 700;
            cadence = 0.9;
            cost = 15;
            timeConst = 2.f;
            break;
        case 2: //vert
            ray = 80;
            puissance = 100;
            cadence = 0.1;
            cost = 20;
            timeConst = 10.f;
            break;
        case 3: //jaune
            ray = 100
            puissance = 70;
            cadence = 0.2;
            cost = 30;
            timeConst = 1.f;
            break;
        case 4: //bleue
            ray = 200;
            puissance = 200;
            cadence = 0.5;
            cost = 10;
            timeConst = 2.f;
            break;
        default:
            break;
    }


    // test de superposition de Tour // 

    Tour *tmpTour = liste;
    while(tmpTour != NULL){
        if(fabs(x-tmpTour->x)<=30 && fabs(y-tmpTour->y)<=30){
            error = 1;
            *message = "On ne peut construire sur une tour";
        }
        tmpTour = tmpTour->next;
    }
    if(*coins-cost < 0){
        *message = "Manque de coins !!!";
        error = 1;
    }
    if(error == 0){
        Tour* nouvelElement = (Tour*)(malloc(sizeof(Tour)));
        if(nouvelElement == NULL){
            fprintf(stderr, "Erreur allocation : Tour\n");
            exit(EXIT_FAILURE);
        }
        nouvelElement->x = x;
        nouvelElement->y = y;
        nouvelElement->rayon = ray;
        nouvelElement->cost = cost;
        nouvelElement->type = type;
        nouvelElement->puissance = puissance; //cout infligé
        nouvelElement->cadence = cadence; //intervalle de temps entre deux tirs
        nouvelElement->active = 0; //1 quandfini d'etre construite
        nouvelElement->timeCrea = (float)SDL_GetTicks(); //1 quand fini d etre construite
        nouvelElement->timeConst = timeConst; //(sec) temps de construction pour cette Tour
        nouvelElement->timeDernierTir = 0.0;
        // paiement
        *coins -=cost;
        nouvelElement->next = NULL;
        if(liste == NULL){
            *message = "NEW Tour";
            return nouvelElement;
        }
        else{
            Tour* temp=liste;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = nouvelElement;
            *message = "Tour ADDED";
            return liste;
        }
    }else{
        return liste;
    }

}


void glisserTour(int x, int y, int type){
    int ray = 0;
    switch(type) {
        case 1:
            ray = 200;
            break;
        case 2:
            ray = 80;
            break;
        case 3:
            ray = 100;
            break;
        case 4:
            ray = 200;
            break;
        default:
            break;
    }
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(x,y,1);
    //rayon d'action
    glColor3ub(220, 250, 255);
        int i;
        glBegin(GL_LINE_LOOP);
        for(i=0; i<30; i++){
            //angle = 2*M_PI*i/30;
            glVertex2f( cos(2*M_PI*i/30)*(ray), sin(2*M_PI*i/30)*(ray));
        }
        glEnd();

    //zone non constructible
    glColor4f(0.0, 0.0, 0.0, 0.1); 
    glBegin(GL_POLYGON);
    for(i=0; i<30; i++){
        //angle = 2*M_PI*i/30;
        glVertex2f( cos(2*M_PI*i/30)*(30), sin(2*M_PI*i/30)*(30));
    }
    glEnd();

    //Tour
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 4);
    glColor4f(1, 1, 1, 0.5);
    glBegin(GL_QUADS);
    //HAUT GAUCHE
    glTexCoord2f(0.25*(type), 0);      glVertex2f(20,20);
    //HAUT DROITE
    glTexCoord2f(0.25*(type-1), 0);   glVertex2f(-20, 20);
    //BAS GAUCHE
    glTexCoord2f(0.25*(type-1), 0.1);         glVertex2f(-20, -20);
    //BAS DROIT
    glTexCoord2f(0.25*(type), 0.1);      glVertex2f(20, -20);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glLoadIdentity();

}

/*SUPPRIMER TOUTES TOURS*/

l_Tour supprimerAllTour(l_Tour liste){
    Tour* tmp = liste;
    while(tmp!=NULL){
        tmp = tmp->next;
        free(tmp);
    }
    return NULL;
}

/*GESTION SELECTION TOURS*/

l_Tour selectTour(l_Tour liste, int x, int y, char** message){
    Tour *tmpTour = liste;
    while(tmpTour != NULL){
        if(fabs(x-tmpTour->x)<=20 && fabs(y-tmpTour->y)<=20){
	    *message = "Tour selectionnee";
            return tmpTour;
        }
        tmpTour = tmpTour->next;
    }
    return NULL;
}

/*SUPPRIMER TOUR*/

l_Tour supprimerTour(l_Tour liste, l_Tour aSuppr){
    /* Liste vide */
    if(liste == NULL)
        return NULL;

    /* Si l'élément doit être supprimé */
    if(liste == aSuppr)
    {
        /* On le supprime en mémorisant
         l'adresse de l'élément suivant */
        Tour* tmp = liste->next;
        free(liste);
        /* L'élément ayant été supprimé, la liste commencera à l'élément suivant */
        tmp = supprimerTour(tmp, aSuppr);
        return tmp;
    }
    else
    {
        /* Si l'élement en cours de traitement ne doit pas être supprimé */
        liste->next = supprimerTour(liste->next, aSuppr);
        return liste;
    }
}

/*AFFICHAGE DE Tour*/

void afficherTour(l_Tour liste, int ray, l_Tour TourSelected){
    Tour *tmp = liste;
    while(tmp != NULL){
        if(((float)SDL_GetTicks() - tmp->timeCrea)/1000 > tmp->timeConst){
            tmp->active = 1;
        }
        glMatrixMode(GL_MODELVIEW);
        glTranslatef(tmp->x,tmp->y,1);

        //cercle d action, si on appui sur t
        if(ray == 1){
            glColor3ub(220, 250, 255);
            int i;
            glBegin(GL_LINE_LOOP);
            for(i=0; i<30; i++){
                //angle = 2*M_PI*i/30;
                glVertex2f( cos(2*M_PI*i/30)*(tmp->rayon), sin(2*M_PI*i/30)*(tmp->rayon));
            }
            glEnd();

            //zone non construtible
            glColor4f(0.0, 0.0, 0.0, 0.1); 
            glBegin(GL_POLYGON);
            for(i=0; i<30; i++){
                //angle = 2*M_PI*i/30;
                glVertex2f( cos(2*M_PI*i/30)*(30), sin(2*M_PI*i/30)*(30));
            }
            glEnd();
        }

        if(tmp == TourSelected){
            int j;
            glColor4f(0.7, 0.0, 0.0, 0.3);
            glBegin(GL_POLYGON);
            for(j=0; j<30; j++){
                glVertex2f( cos(2*M_PI*j/30)*(15), sin(2*M_PI*j/30)*(15));
            }
            glEnd();
        }

        if(tmp->active == 0){
            glBindTexture(GL_TEXTURE_2D, 4);
            glColor4f(1, 1, 1, 0.2);
            glBegin(GL_QUADS);
            //HAUT GAUCHE
            glTexCoord2f(0.25*(tmp->type), 0);      glVertex2f(20,20);
            //HAUT DROITE
            glTexCoord2f(0.25*(tmp->type-1), 0);   glVertex2f(-20, 20);
            //BAS GAUCHE
            glTexCoord2f(0.25*(tmp->type-1), 0.1);         glVertex2f(-20, -20);
            //BAS DROIT
            glTexCoord2f(0.25*(tmp->type), 0.1);      glVertex2f(20, -20);
            glEnd();
        }else{ //Tour
            glBindTexture(GL_TEXTURE_2D, 4);
            glColor3ub(255, 255, 255);
            glBegin(GL_QUADS);
            //HAUT GAUCHE
            glTexCoord2f(0.25*(tmp->type), 0);      glVertex2f(20,20);
            //HAUT DROITE
            glTexCoord2f(0.25*(tmp->type-1), 0);   glVertex2f(-20, 20);
            //BAS GAUCHE
            glTexCoord2f(0.25*(tmp->type-1), 0.1);         glVertex2f(-20, -20);
            //BAS DROIT
            glTexCoord2f(0.25*(tmp->type), 0.1);      glVertex2f(20, -20);
            glEnd();

        }
        glBindTexture(GL_TEXTURE_2D, 0);
        glLoadIdentity();
        tmp = tmp->next;
    }

}

/*GESTION DES TOURS*/

void gestionTour(l_Tour listeTour, l_Monstre listeMonstre){

    Tour *tmpTour = listeTour;
    Monstre *tmpMonstre = listeMonstre;
    Monstre *Cible;
    float distance;
    float distanceCible;
    float resistTour = 1;
    while(tmpTour != NULL){
        tmpMonstre = listeMonstre;
        if(tmpTour->active==1 && (SDL_GetTicks()/1000.f - tmpTour->timeDernierTir)>tmpTour->cadence){
            tmpTour->timeDernierTir = SDL_GetTicks()/1000.f;
            Cible = tmpMonstre;
            while(tmpMonstre != NULL){
                if(tmpMonstre->go == 1){
                    //gestionde la resistance a chaque type de tourelle
                    switch (tmpTour->type) {
                        case 1:
                            resistTour = tmpMonstre->resistTour1;
                            break;
                        case 2:
                            resistTour = tmpMonstre->resistTour2;
                            break;
                        case 3:
                            resistTour = tmpMonstre->resistTour3;
                            break;
                        case 4:
                            resistTour = tmpMonstre->resistTour4;
                            break;
                        default:
                            resistTour = 1;
                            break;
                    }
                    //recherche du Monstre le plus proche
                    distanceCible = sqrt(((tmpTour->x)-(Cible->x))*((tmpTour->x)-(Cible->x))+((tmpTour->y)-(Cible->y))*((tmpTour->y)-(Cible->y)));
                    distance = sqrt(((tmpTour->x)-(tmpMonstre->x))*((tmpTour->x)-(tmpMonstre->x))+((tmpTour->y)-(tmpMonstre->y))*((tmpTour->y)-(tmpMonstre->y)));
                    //si la Tour est de type 3 (jaune) elle tir sur tout le monde en meme temps
                    if(tmpTour->type==3 && distance<tmpTour->rayon){

                        glBegin(GL_LINES);
                        glColor3f(0.0,1.0,0.0);
                        glVertex2f(tmpTour->x,tmpTour->y);
                        glVertex2f(tmpMonstre->x,tmpMonstre->y);
                        glEnd();
                        glLoadIdentity();
                        tmpMonstre->vie=(tmpMonstre->vie)-(tmpTour->puissance*resistTour);

                    }

                    if(distance<distanceCible){
                        Cible = tmpMonstre;
                        distanceCible=distance;
                    }
                }
                tmpMonstre = tmpMonstre->next;
            }

            //le montre perd de la vie s'il est dans le rayon d action de la Tour
            //sauf si la Tour est de type 3 car a déjà perdu de la vie
            if(distanceCible<(tmpTour->rayon) && tmpTour->type!=3){
                Cible->vie=(Cible->vie)-(tmpTour->puissance*resistTour);
            }
            // si on est dans le rayon d action de la Tour
            if(distanceCible<tmpTour->rayon && tmpTour->type!=3){
                //dessin de tir
                glBegin(GL_LINES);
                glColor3f(1.0f,0.0,0.0);
                glVertex2f(tmpTour->x,tmpTour->y);
                glVertex2f(Cible->x,Cible->y);
                glEnd();
                glLoadIdentity();

            }
        }
        tmpTour = tmpTour->next;
    }

}
