#ifndef BST_H
#define BST_H

typedef struct no_avl{
    int raiz;
    int fator; //fator de balanço
    struct no_avl *esq, *dir; //ponteiros p esquerda e direita da árvore
}no_avl;

typedef no_avl * arvore;

int altura(arvore a);

void incializar(arvore *a);

arvore inserir(arvore a, int v, int *cresceu);
arvore remover(arvore a, int v, int *diminuiu);

// ROTAÇÕES

arvore rotacionar(arvore a); //fazer todas as chamadas de processo de rotação
arvore simples_direita(arvore a);
arvore simples_esquerda(arvore a);
arvore dupla_direita(arvore a);
arvore dupla_esquerda(arvore a);

// IMPRIMIR

void imprimir(arvore raiz);
void imprimir_elemento(arvore raiz);

#endif
