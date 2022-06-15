#ifndef BST_H
#define BST_H

typedef struct no{
    int valor;
    struct no* esq, *dir;
} no;

typedef no* arvore;

arvore inserir (arvore a, int v);
arvore remover (arvore a, int v);

int qntPrimos (arvore a);

int existe (arvore a, int v);
int menor (arvore a);

void sucessor (arvore a, int v);

void preorder (arvore a);
void inorder (arvore a);
void posorder (arvore a);
void reverso (arvore a);

int altura (arvore a);

void caminho (arvore a, int v);

#endif
