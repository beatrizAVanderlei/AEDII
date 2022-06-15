#include <stdio.h>
#include <stdlib.h>
#include "profundidade.h"

int contador;

//grafo

grafo *criar_grafo(int tamanho){
        
    grafo * g = malloc(sizeof(grafo));
    
    g->tamanho = tamanho;
    g->mapa = (char *)malloc(sizeof(char) * tamanho);
    g->lista = malloc(tamanho * sizeof(no));
    g->visitado = malloc(tamanho * sizeof(no));

    for(int i=0; i<tamanho; i++){
        g->lista[i] = NULL; 
        g->visitado[i] = 0; 
    }
    
    return g;
}


no * novo_vertice(int v){
    
    no * novo = malloc(sizeof(no));
    novo->vertice = v;
    novo->prox = NULL;
    return novo;
    
}


void adicionar_aresta(grafo *g, int v1, int v2){
    
    no * novo = novo_vertice(v2);
    novo->prox = g->lista[v1];
    g->lista[v1] = novo;
    novo = novo_vertice(v1);
    novo->prox = g->lista[v2];
    g->lista[v2] = novo;
    
}


int indice(grafo *g, char c){
    
    for(int i=0; i<g->tamanho; i++){
        if(c == g->mapa[i]){
            return i;
        }
    }
    return -1;
}


void imprime_grafo(grafo* g){
    
    for (int i = 0; i < g->tamanho; i++){
        
        no* p = g->lista[i];
        printf("%c: ", g->mapa[i]);
        
        while (p!=NULL){
            printf("%c ", g->mapa[p->vertice]);
            p = p->prox;
        }
        printf("\n");
    }
    
    printf("\n");
    
}


grafo * iniciar_grafo(grafo *g){
    
    FILE *input;
    input = fopen("entrada2.txt", "r");
    
    int vertices, arestas, i;
    char aresta1, aresta2, c;

    fscanf(input, "%d %d", &vertices, &arestas);
    g = criar_grafo(vertices);

    for(i=0; i<vertices; i++){
        c = fgetc(input); //tira o \n do final de cada linha
        g->mapa[i] = fgetc(input);
    }

    for(i=0; i<arestas; i++){
        c = fgetc(input); //tira o \n do final de cada linha
        aresta1 = fgetc(input);
        aresta2 = fgetc(input);
        adicionar_aresta(g, indice(g, aresta1), indice(g, aresta2));
    }
        
    fclose(input);
    return g;
}

//busca em profundidade

void DFS (grafo *g){
    
    enum cor cores[g->tamanho];
    char predecessor[g->tamanho];
    int inicio[g->tamanho];
    int fim[g->tamanho];
    
    for(int u = 0; u < g->tamanho; u++){
        cores[u] = BRANCO;
        predecessor[u] = '0';
        inicio[u] = 0;
        fim[u] = 0;
    }
    
    contador = 0;
    
    for(int u = 0; u < g->tamanho; u++){
        if(cores[u] == BRANCO)
            DFS_VISIT(g, u, cores, predecessor, inicio, fim);
    }
    
    printf("CORES: ");
    
    for(int i = 0; i < g->tamanho; i++){
        switch(cores[i]){
            case 0:
                printf("BRANCO ");
            case 1:
                printf("CINZA ");
            case 2:
                printf("PRETO ");
        }
    }
    
    printf("\n");
    
    printf("DESCOBERTO: ");
    for(int i = 0; i < g->tamanho; i++){
        printf("%d ", inicio[i]);
    }
    
    printf("\n");
    
    printf("FINALIZADO: ");
    for(int i = 0; i < g->tamanho; i++){
        printf("%d ", fim[i]);
    }
    
    printf("\n");
    
    printf("PREDECESSORES: ");
    for(int i = 0; i < g->tamanho; i++){
        printf("%c ", predecessor[i]);
    }
    
    printf("\n");
    
}


void DFS_VISIT (grafo *g, int u, enum cor *cores, char *predecessor, int *inicio, int *fim){
    
    cores[u] = CINZA;
    contador++;
    inicio[u] = contador;
    
    no * p = g->lista[u];
        //printf("%c: ", g->mapa[u]);
        
        while (p!=NULL){
            //printf("%c ", g->mapa[p->vertice]);
            
            if(cores[p->vertice] == BRANCO){
                //printf("%c ", g->mapa[p->vertice]);
                predecessor[p->vertice] = g->mapa[u];
                DFS_VISIT(g, p->vertice, cores, predecessor, inicio, fim);
            }
            
            p = p->prox;
        }
        //printf("\n");
    
    cores[u] = PRETO; 
    fim[u] = ++contador;
    
}
