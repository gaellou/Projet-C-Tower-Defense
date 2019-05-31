#ifndef __TEXTURE_H__
#define __TEXTURE_H__



Uint32 obtenirPixel(SDL_Surface *surface, int x, int y);
GLuint* texture(int **tab, char** nomFichierImage);

#endif