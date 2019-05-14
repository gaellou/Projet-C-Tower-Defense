#ifndef __NODE_H__
#define __NODE_H__




typedef struct s_node{
    int x;
    int y;
    struct s_node* next;
} node;
typedef node* l_node;

#endif