#ifndef KRUSKAL_H
#define KRUSKAL_H


typedef struct grafo{
    int tamanho;
    char *mapa;
    int **matrix;
}grafo;

typedef struct aresta{
    char u;
    char v;
    int peso;
} aresta;

typedef struct lista_arestas{
    aresta arestas[1000]; //valor aleatorio, precisa ser maior que a quantidade de arestas
    int quantidade;
}lista_arestas;

//grafo

grafo * criar_grafo (int tamanho);
grafo * iniciar_grafo (grafo *g);
void adicionar_arestan(grafo *g, int v1, int v2, int peso);
void imprime_Adj_matrix (grafo *g);
int indice (grafo *g, char c);

//kruskal

void sort (lista_arestas *l);
int buscar (int *pertence, int v);
void aplicar_uniao (grafo *g, int *pertence, int va, int vb);
void imprime (grafo *g, lista_arestas *mst);
void kruskal (grafo *g);

#endif 
