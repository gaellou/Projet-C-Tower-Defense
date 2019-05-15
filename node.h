#ifndef __NODE_H__
#define __NODE_H__




typedef struct s_node{
    int x;
    int y;
    struct s_node* next;
} node;
typedef node* l_node;

l_node ajouterNode(l_node liste, int x, int y);
void afficherNodes(l_node liste);
l_node supprimerAllNode(l_node liste);

#endif