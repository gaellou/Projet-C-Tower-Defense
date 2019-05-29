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

l_Monstre genereVague(int vague, l_Monstre monst, int nbMonstre, l_node ma_liste){
	float resistTour1 = 1;
	float resistTour2 = 1;
	float resistTour3 = 1;
	float resistTour4 = 1;

	if (vague == 5){
		resistTour1 =0.5;
	}
	if (vague == 10){
		resistTour2 = 0.5;
	}
	if (vague == 15){
		resistTour2 = 0.3;
		resistTour3 = 0.5;
	}
	if (vague == 20){
		resistTour2 = 0.7;
		resistTour3 = 0.5;
		resistTour4 = 0.5;
	}
	int idmonstre=0;
    int vie = vague*1000;
    for(idmonstre=0;idmonstre<nbMonstre;idmonstre++){
        monst=ajouterMonster(monst, ma_liste, idmonstre, vie, 1, resistTour1, resistTour2, resistTour3, resistTour4);
    }
    return monst;
}