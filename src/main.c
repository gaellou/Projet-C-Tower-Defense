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
#include "texture.h"


#include "texte.h"
#include "chemin.h"
#include "map.h"

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
printf("itd ok\n");
    /*---------------------------------------------------------------------------------------
                    VALIDATION FICHIER ITD PAS IMPLEMENTEE ON CHARGE DIRECTEMENT LA MAP
     ----------------------------------------------------------------------------------------*/

    //Initialisation des tableaux rgb grâce à GLubyte

    GLubyte couleurChemin[3] ={255,255,255};

    GLubyte couleurNoeudIn[3] = {0,200,0};
    GLubyte couleurNoeudOut[3] ={200,0,0};

    // récuperer le nom de l'image de map au sein du fichier itd
    char label[20] = "images/map1.ppm";
    char* nomFichierImage = label;

    l_node ma_liste = NULL;
    //On ajoute les coordonnées des noeuds
    ma_liste = addCoordNoeud(fileName); 
    printf("%d %d \n", ma_liste->x, ma_liste->y);//dans fichier map

printf("liste noeud ok\n");

    //Liste des Monstre//
    l_Monstre monst=NULL;

    //Liste des Tour//
    l_Tour Tours=NULL;
    l_Tour TourSelected=NULL;

    //Paramètre le mode vidéo avec une largeur, hauteur, et le nombre
    //de bits par pixel.
    setVideoMode();
    //Nom de la fenêtre.
    SDL_WM_SetCaption("Guinea Pig Attack - Tower Defense", NULL);
    //Specifie le diamètre des points rasterisés.
    glPointSize(20);

printf("videomode ok\n");
    /*--------------------------------------------------------------
                            VARIABLES JEU
     --------------------------------------------------------------*/
printf("init variables \n");
    //position cursor
    int xClicked = -1, yClicked=-1;
    int xMove = -1, yMove=-1;
printf("cursor ok \n");
    //pause help
    int pause = 1;
 
    printf("pauseok\n");
    //bonhomme qui bouge
    int bouge = 0;
    printf("mvt ok\n");
    //gagne ou perdu
    int WinLose = 0;
    printf("winloose ok\n");
    //vague
    int vague = 1;
    float timeVague;
    timeVague = 0.0;
    int WinVague =0 ;
    printf("vague ok\n");
    //time
    Uint32 startTime;
    startTime = 0.0;
    float SecDixieme = 0;
    float dernierMouv = 0;
    printf("time ok\n");
    //player
    int coins = 250;
    printf("coins ok\n");

    //message
    char** message;
    message =  (char**)(malloc(50*sizeof(char)));
    if(message == NULL){
        fprintf(stderr, "Erreur allocation : MESSAGE\n");
        exit(EXIT_FAILURE);
    }
    *message = NULL;
    printf("message ok\n");

    //gestion d'évennement
    int TourTypeSelected = 0;
    int RaySelected = 0;
    printf("event ok\n");
    //On crée le pointeur sur la texture.
    GLuint* textureId;
    textureId = texture(tab, &nomFichierImage);
    printf("TEXTURE OK\n");

printf("variables ok\n");
    /*--------------------------------------------------------------
                        GESTION DE L'AFFICHAGE
     --------------------------------------------------------------*/

    int loop = 1;
    printf("lancement du jeu\n");
    TourTypeSelected = 1;
    genereVague(vague, &monst, 10, ma_liste);
    printf("%d\n",monst->next->vie );

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
          if(pause == 1 ){
                if(vague == 50 && monst==NULL){

                    WinLose = 1;
                }
                if(WinLose == 0 && WinVague == 1){
                    
                    if(vague !=0 && monst==NULL){
                        timeVague = 2.0;
                        vague++;
                    }
                  
                   timeVague += startTime;
                    genereVague(vague, &monst, 51, ma_liste);
                    WinVague = 0;

                   
                   
               }
           }


            else{
            }
            //on supprime les Monstre tués
            l_Monstre tmpMonstre;
            tmpMonstre = monst;
           
                if(tmpMonstre!=NULL){
                if(tmpMonstre->vie <= 1){
                    monst = supprimerMonstre(monst, tmpMonstre->idmonstre);
                    coins +=5+vague-1;
                    printf("deplacement");
                }
                tmpMonstre=tmpMonstre->next;
            }
            else{ }



           
                if(monst!=NULL){
                   
                    // on gere les deplacement des Monstres*/
                    deplaceMonstre(monst,((float)startTime)/1000, vague, message, &bouge, &WinLose);

                    // gestiondes tir des Tour
                    gestionTour(Tours, monst);

                }else{
                    WinVague = 1;
                    printf("\033[37;41m");
                    printf("YOU WIN Vague : %d\n", vague);
                    printf("\033[30;49m");
                }

            
            
            AfficherMonstre (monst, vague, &bouge);

           
        }//FIN IF WinLose
        else{
            Tours = supprimerAllTour(Tours);
            monst = supprimerAllMonstre(monst);
            if(WinLose == 1){//WINNER
                afficherMenuWin( WinLose);
                pause = 1;
                vague = 0;
                coins = 100;
            }
            if(WinLose == 2){//LOSER
                afficherMenuLose( WinLose);
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
        afficherMouse(xMove, yMove, PIXEL_HEIGHT);
        //Affiche le curseur.
        

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
                                        //gestion creation de Tour
                    
                            if(TourTypeSelected != 0){
                        
                            
                                Tours = ajouterTour(Tours, &coins, xClicked, yClicked, TourTypeSelected, message);
                                printf("tour construite\n");}
                            else{
                                *message = "Select Type (1, 2, 3, 4) !!! ";
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
                        case 'c':
                            TourTypeSelected =1;
                            break;
                        case 'v' :
                            TourTypeSelected = 2;
                            break;
                        case 'b' :
                            TourTypeSelected = 3;
                            break;
                        case 'n' :
                            TourTypeSelected = 4;
                            break;
                        case 's' :
                            vague = 1;
                            break;
                        case 'w' :
                            WinLose = 1;
                            break;
                        case 'l' :
                            WinLose= 2;
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
    }}
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