#ifndef __TEXTE_H__
#define __TEXTE_H__

void afficheMessageErreur();
GLuint* afficheCoins(GLuint* textureId, int coins);
GLuint* afficheTexte(GLuint* textureIs, int x, int y, char *Texte, int r, int g, int b, int size);
GLuint* afficheVagues(GLuint* textureId, int vague);

#endif