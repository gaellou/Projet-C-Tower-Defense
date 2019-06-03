#define M_PI 3.14159

#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_image.h>

#include <SDL/SDL_ttf.h> /*bibliothèque texte*/

#include "monstre.h"
#include "tour.h"



/*AJOUTER TOUR*/

l_Tour ajouterTour(l_Tour liste, int* coins, int x, int y,int type, char** message){
    int error = 0;
    int ray;
    int puissance;
    float cadence;
    int cost;
    float timeConst;
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
            ray = 200;
            puissance = 100;
            cadence = 0.1;
            cost = 20;
            timeConst = 10.f;
            break;
        case 3: //jaune
            ray = 200;
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

//test monaie
    if(*coins-cost < 0){
        *message = "Manque de coins !!!";
        error = 1;
    }

//erreur d'allocation
    if(error == 0){
        Tour* nouvelElement = (Tour*)(malloc(sizeof(Tour)));
        if(nouvelElement == NULL){
            fprintf(stderr, "Erreur allocation : Tour\n");
            exit(EXIT_FAILURE);
        }
        nouvelElement->x = x;
        nouvelElement->y = y;
        nouvelElement->ray = ray;
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
            printf("Tour ADDED");
            return liste;
        }
    }else{
        return liste;
    }

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
                glVertex2f( cos(2*M_PI*i/30)*(tmp->ray), sin(2*M_PI*i/30)*(tmp->ray));
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
                    if(tmpTour->type==3 && distance<tmpTour->ray){

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
            if(distanceCible<(tmpTour->ray) && tmpTour->type!=3){
                Cible->vie=(Cible->vie)-(tmpTour->puissance*resistTour);
            }
            // si on est dans le rayon d action de la Tour
            if(distanceCible<tmpTour->ray && tmpTour->type!=3){
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
