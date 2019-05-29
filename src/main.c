#define M_PI 3.1415

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <math.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_image.h>

#include <SDL/SDL_ttf.h> /*bibliothèque texte*/


#undef main

#include "affichage.h"
#include "vague.h"
#include "node.h"
#include "tour.h"
#include "monstre.h"
//#include "texture.h"
//#include "carte.h"

//#include "texte.h"
#include "chemin.h"
//#include "map.h"

static unsigned int WINDOW_WIDTH = 1000;
static unsigned int WINDOW_HEIGHT = 800;

static unsigned int PIXEL_HEIGHT = 800;

static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


int main(int argc, char** argv) {

    /*--------------------------------------------------------------
     INITIALISATION
     --------------------------------------------------------------*/

    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    /*--------------------------------------------------------------
                    INITIALISATION SDL TTF POUR LE TEXTE
     --------------------------------------------------------------*/

    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    /*--------------------------------------------------------------
                    DÉCLARATION ET ALLOCATION
                   QUI FAIT LA TAILLE DE L'IMAGE
                    ET QUI PERMET DE SAVOIR SI
                 UNE ZONE EST CONSTRUCTIBLE OU NON
                1 CONSTRUCTIBLE, 0 NON CONSTRUCTIBLE
     --------------------------------------------------------------*/

    //Déclaration du tabl de construction
    int **tab = (int**) malloc(730 * sizeof(int*));//hauteur
    size_t i;
    for(i = 0 ; i < 1000 ; i++)
        tab[i] = (int*)(malloc(1000 * sizeof(int))); //largeur
    if(tab == NULL){
        fprintf(stderr, "Erreur allocation : tab\n");
        exit(EXIT_FAILURE);
    }

    /*--------------------------------------------------------------
                ON DEMANDE À L'UTILISATEUR DE RENTRER
                LE NOM DU FICHIER ITD, S'IL N'EXISTE PAS
                            ON ARRÊTE LÀ.
     --------------------------------------------------------------*/

    //chargement nom fichier
    char fileName2[15];
    char fileName[30] = "data/";
    printf("NOM DU FICHIER À CHARGER ex : map1.itd : ");
    scanf("%s", fileName2);
    strcat(fileName,fileName2);
    printf("TEXTE FICHIER À CHARGER : %s", fileName);

    FILE *fIn;
    if ( (fIn = fopen ( fileName, "r" ) ) == NULL )
    {
        printf ( "MAIN : fichier non-existant!\n" );
        SDL_Quit();
        return EXIT_FAILURE;
    }
    else
    {
        printf ( "Le fichier existe!\n" );
        fclose ( fIn );
    }

    /*---------------------------------------------------------------------------------------
                    VALIDATION FICHIER ITD PAS IMPLEMENTEE ON CHARGE DIRECTEMENT LA MAP
     ----------------------------------------------------------------------------------------*/

    //Initialisation des tableaux rgb grâce à GLubyte
    GLubyte couleurConstruct[3] = {255,200,80};
    GLubyte couleurChemin[3] ={255,255,255};
    GLubyte couleurNoeud[3] = {0,0,0};
    GLubyte couleurNoeudIn[3] = {0,200,0};
    GLubyte couleurNoeudOut[3] ={200,0,0};

    // récuperer le nom de l'image de map au sein du fichier itd
    char label[20] = "images/";
    char* nomFichierImage = label;

    l_node ma_liste = NULL;
    //On ajoute les coordonnées des noeuds
    ma_liste = addCoordNoeud(fileName); //dans fichier map



    //Liste des Monstre//
    l_Monstre monst=NULL;

    //Liste des Tour//
    l_Tour Tours=NULL;
    l_Tour TourSelected=NULL;

    /*--------------------------------------------------------------
                    DÉCLARATION DES SONS DU JEU
     --------------------------------------------------------------*/



    //Paramètre le mode vidéo avec une largeur, hauteur, et le nombre
    //de bits par pixel.
    setVideoMode();
    //Nom de la fenêtre.
    SDL_WM_SetCaption("Tower Defense", NULL);
    //Specifie le diamètre des points rasterisés.
    glPointSize(20);


    /*--------------------------------------------------------------
                            VARIABLES JEU
     --------------------------------------------------------------*/

    //position cursor
    int xClicked = -1, yClicked=-1;
    int xMove = -1, yMove=-1;
    //pause help
    int pause = 1;
    int help = 0;
    //bonhomme qui bouge
    int bouge = 0;
    //gagne ou perdu
    int WinLose = 0;
    //Si c'est le début du jeu
    int gameStart = 1;
    //vague
    int vague = 0;
    float timeVague;
    timeVague = 0.0;
    //time
    Uint32 startTime;
    startTime = 0.0;
    float SecDixieme = 0;
    float dernierMouv = 0;
    //player
    int coins = 100;

    //message
    char** message;
    message =  (char**)(malloc(50*sizeof(char)));
    if(message == NULL){
        fprintf(stderr, "Erreur allocation : MESSAGE\n");
        exit(EXIT_FAILURE);
    }
    *message = NULL;

    //gestion d'évennement
    int TourTypeSelected = 0;
    int RaySelected = 0;
    //On crée le pointeur sur la texture.
    GLuint* textureId;
    textureId = texture(tab, &nomFichierImage);

    /*--------------------------------------------------------------
                        GESTION DE L'AFFICHAGE
     --------------------------------------------------------------*/

    int loop = 1;
    while(loop) {
        glClear(GL_COLOR_BUFFER_BIT);
        SecDixieme = (float)SDL_GetTicks()/1000.f;

        /* dessin */

        glMatrixMode(GL_MODELVIEW);
        DessinMap(); //On affiche la map

        //chemin
        if(RaySelected == 1){
            chemin(ma_liste,couleurChemin[0],couleurChemin[1],couleurChemin[2], couleurNoeudIn[0], couleurNoeudIn[1], couleurNoeudIn[2], couleurNoeudOut[0], couleurNoeudOut[1], couleurNoeudOut[2]);
        }

        //Prend la position du curseur
        SDL_GetMouseState(&xMove, &yMove);

        // si la partie est en cours
        if(WinLose == 0){

            // affichage des Tour
            afficherTour(Tours, RaySelected, TourSelected);

            //gestion des vagues
            if(monst==NULL && pause == 0){
                if(vague == 20){
                    WinLose = 1;
                }
                if(WinLose == 0){
                    vague++;
                    if(vague == 1){
                        timeVague = 0.0;
                    }
                    timeVague += startTime;
                    monst = genereVague(vague, monst, 10,ma_liste);
                    //genereVague(int vague, l_Monstre monst, l_node ma_liste, int nbMonstre);
                   
                }
            }

            else{
                startTime = SDL_GetTicks() - timeVague;
            }

            //on supprime les Monstre tués
            l_Monstre tmpMonstre;
            tmpMonstre = monst;
            while(tmpMonstre != NULL){
                if(tmpMonstre->vie<1){
                    monst = supprimerMonstre(monst, tmpMonstre->idmonstre);
                    coins +=5+vague-1;
                }
                tmpMonstre=tmpMonstre->next;
            }

            /*--------------------------------------------------------------
                                GESTION DES 10 MS.
             --------------------------------------------------------------*/

            //si il s'est passé 0.1 sec depuis la dernière gestion des evenements
            if(SecDixieme-dernierMouv > 0.1 && pause == 0){
                dernierMouv = SecDixieme;
                //gestion Monstre
                if(monst!=NULL){
                    // on gere les deplacement des Monstres
                    deplaceMonstre(monst,((float)startTime)/1000, vague, message, &bouge, &WinLose);

                    // gestiondes tir des Tour
                    gestionTour(Tours, monst);

                }else{
                    printf("\033[37;41m");
                    printf("YOU WIN Vague : %d\n", vague);
                    printf("\033[30;49m");
                }

            }
            // affichage des Monstre
            AfficherMonstre (monst, vague, &bouge);

            //glissage de la Tour selected
            /*if(TourTypeSelected != 0){
                glisserTour(xMove, PIXEL_HEIGHT-yMove, TourTypeSelected);
            }*/

        }//FIN IF WinLose
        else{
            Tours = supprimerAllTour(Tours);
            monst = supprimerAllMonstre(monst);
            if(WinLose == 1){//WINNER
             
                pause = 1;
                vague = 0;
                coins = 100;
            }
            if(WinLose == 2){//LOSER
       
                pause = 1;
                vague = 0;
                coins = 100;
            }
        }

        //on affiche le message
        if(*message != NULL){
            afficheMessageErreur();
            afficheTexte(textureId, 250, 610, *message, 255, 255, 255, 20);
        }

        //On affiche l'argent et le nombre de vague en cours
        afficheCoins(textureId, coins);
        afficheVagues(textureId, vague);


        //on retire le curseur de base
        SDL_ShowCursor(0);
        //Affiche le curseur.
        //afficherMouse(xMove, yMove, PIXEL_HEIGHT);

        SDL_GL_SwapBuffers();
        /* ****** */

        /*--------------------------------------------------------------
                    GESTION DES ÉVÉNNEMENTS LIÉES AU CLIK
         --------------------------------------------------------------*/
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }
            switch(e.type) {
                case SDL_MOUSEBUTTONDOWN:
                    
                    xClicked = e.button.x;
                    yClicked = (PIXEL_HEIGHT-e.button.y);
                    TourTypeSelected = 1;
                    //gestion creation de Tour
                    if(pause ==  0 && yClicked<730 && TourTypeSelected != 0){
                        if(xClicked!=-1 && yClicked!=-1){
                            if(tab[730-yClicked][xClicked] == 1){
                                Tours = ajouterTour(Tours, &coins, xClicked, yClicked, TourTypeSelected, message);
                            }else{
                                *message = "Zone non constructible !!! ";
                            }
                        }
                    }

                    break;
                case SDL_MOUSEBUTTONUP:
                    xClicked = -1;
                    yClicked = -1;
                    break;

                case SDL_VIDEORESIZE:
                    WINDOW_WIDTH = e.resize.w;
                    WINDOW_HEIGHT = e.resize.h;
                    setVideoMode();
                    break;
                       
                /*--------------------------------------------------------------
                        BOUCLE DE GESTION DES ÉVÉNNEMENTS CLAVIER
                --------------------------------------------------------------*/

                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                        case 'q' :
                            exit(1);
                            break;
                        case SDLK_p:
                            if(pause == 1){
                               
                                pause = 0;
                            }else{
                                
                                pause = 1;
                            }
                            gameStart = 0;
                            break;
                        case SDLK_BACKSPACE:
                           
                            break;
                        case SDLK_ESCAPE:
                           
                            loop = 0;
                            break;
                        default : break;
                     } 

        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }
}
}
    /*--------------------------------------------------------------
                    FREE DES ALLOCATIONS MÉMOIRE
     --------------------------------------------------------------*/

    Tours = supprimerAllTour(Tours);
    if(Tours == NULL){
        printf("TourS SUPP \n");
    }
    monst = supprimerAllMonstre(monst);
    if(Tours == NULL){
        printf("Monstre SUPP \n");
    }
    ma_liste = supprimerAllNode(ma_liste);
    if(ma_liste == NULL){
        printf("NODE SUPP \n");
    }
    free(message);

   

    /*--------------------------------------------------------------
                ON FERME SDL TTF SDL MIXER ET LA SDL
     --------------------------------------------------------------*/

    TTF_Quit(); //Fermeture de sdl ttf
    SDL_Quit(); //Fermeture de la sdl

    return EXIT_SUCCESS;
}