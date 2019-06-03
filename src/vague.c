#define M_PI 3.14159

#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_image.h>

#include <SDL/SDL_ttf.h> 

#include "vague.h"
#include "node.h"
#include "monstre.h"

//generation de vague de monstre de differente resistance au differents types de tour suivant l'avancé du jeu//

 void genereVague(int vague, l_Monstre* monst, int nbMonstre, l_node ma_liste){
	float resistTour1 = 0.5;
	float resistTour2 = 0.7;
	float resistTour3 = 0.5;
	float resistTour4 = 0.6;

	/*if (vague <= 5){
		resistTour1 =0.5;
	}
	if (vague <= 10){
		resistTour2 = 0.5;
	}
	if (vague <= 15){
		resistTour2 = 0.3;
		resistTour3 = 0.5;
	}
	if (vague <= 50){
		resistTour2 = 0.7;
		resistTour3 = 0.5;
		resistTour4 = 0.5;
	}*/

    int vie = vague*1000;
    for(int idmonstre=0;idmonstre<nbMonstre;idmonstre++){
      ajouterMonstre(monst, ma_liste, idmonstre, vie, 1, resistTour1, resistTour2, resistTour3, resistTour4);

    }
    
}