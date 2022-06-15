#ifndef LARGURA_H
#define LARGURA_H

enum cor {BRANCO, CINZA, PRETO};

typedef struct grafo{
    int tamanho; //quantidade de vertices
    char *mapa;
    int *visitado;
    int **matriz;
}grafo;

typedef struct fila{
    int tamanho;
    int *itens;
    int primeiro;
    int ultimo;
}fila;

// grafo

grafo * iniciar_grafo (grafo *g); //gerar um grafo a partir de um arquivo
grafo * criar_grafo (int tamanho);
void adicionar_aresta (grafo *g, int v1, int v2);
void imprime_matriz (grafo *g);
int indice (grafo *g, char vertice);

//filas

fila * criar_fila (int tamanho);
void adicionar (fila *f, int valor);
int remover (fila *f);
void imprimir_fila (fila *f, grafo *g);
int vazio (fila *f);

//busca

void auxiliar(char vertice, fila *f, grafo *g);
void busca_largura(int vertice, fila *f, grafo *g);

#endif
