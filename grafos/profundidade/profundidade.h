#ifndef PROFUNDIDADE_H
#define PROFUNDIDADE_H

enum cor {BRANCO, CINZA, PRETO};

typedef struct no{
    char *v;
    int vertice;
    struct no *prox;
}no;


typedef struct grafo{
    int tamanho;
    char *mapa;
    int *visitado;
    no **lista;
}grafo;

//grafo;

grafo * criar_grafo (int tamanho);
no * novo_vertice (int v);
void adicionar_aresta (grafo *g, int v1, int v2);
int indice (grafo *g, char c);
grafo * iniciar_grafo (grafo *g);
void imprime_grafo (grafo* g);

//busca em profundidade 

void auxiliar (grafo *g, char v);
void DFS (grafo *g);
void DFS_VISIT (grafo *g, int u, enum cor *cores, char *predecessor, int *inicio, int *fim);

#endif
