#include <stdio.h>
#include <stdlib.h>
#include "largura.h"

//grafos

int indice(grafo *g, char vertice){ //retorna o indice do vertice no mapa
    
    for(int i = 0; i<g->tamanho; i++){
        if(vertice == g->mapa[i])
            return i;
    }
    
    return -1;
    
}


void adicionar_aresta(grafo *g, int v1, int v2){ //adicioar a aresta na forma de grafo
    g->matriz[v1][v2] = 1;
    g->matriz[v2][v1] = 1;
    
}


grafo * criar_grafo(int tamanho){ //criar grafo na representação de matriz
    
    grafo *g = malloc(sizeof(grafo));
    
    g->tamanho = tamanho;
    g->mapa = (char*) malloc(sizeof(char) * tamanho);
    g->matriz = (int**) malloc(sizeof(int*) * tamanho);
    g->visitado = malloc(sizeof(int) * tamanho);
    
    int i, j;
    
    for(i = 0; i < g->tamanho; i++){
        g->matriz[i] = (int*) malloc(sizeof(int) * tamanho);
        g->visitado[i] = BRANCO;
    }
    
    g->visitado[tamanho] = BRANCO;
    
    for(i = 0; i < g->tamanho; i++){
        for(j = 0; j < g->tamanho; j++){
            if(i == j)
                g->matriz[i][j] = 1;
            else
                g->matriz[i][j] = 0;
        }
    }
    
    return g;   
    
}


grafo * iniciar_grafo(grafo *g){ //gerar um grafo a partir de um arquivo
    
    FILE *entrada;
    entrada = fopen("entrada.txt", "r");
    
    int vertice, arestas, peso;
    char aresta1, aresta2, c;
    
    fscanf(entrada, "%d %d", &vertice, &arestas);
    
    g = criar_grafo(vertice);
    
    for(int i = 0; i < vertice; i++){
        c = fgetc(entrada); //tirar o \n
        g->mapa[i] = fgetc(entrada);        
    }
    
    for(int i = 0; i < arestas; i++){
        c = fgetc(entrada); //tirar o \n
        aresta1 = fgetc(entrada);
        aresta2 = fgetc(entrada);
        adicionar_aresta(g, indice(g, aresta1), indice(g, aresta2));
    }
    
    fclose(entrada);
    return g;
    
}


void imprime_matriz(grafo *g){ //imprimir o grafo na forma de matriz
    
    int i, j;
    
    printf("\n  ");
    for(i = 0; i < g->tamanho; i++){
        printf("%c ", g->mapa[i]);
    }
    
    printf("\n");
    
    for(i = 0; i < g->tamanho; i++){
        
        printf("%c ", g->mapa[i]);
        
        for(j = 0; j < g->tamanho; j++){
            printf("%d ", g->matriz[i][j]);
        }
        
        printf("\n");
    }
    
    printf("\n");
    
}

//filas

int vazio (fila *f){
    
    if(f->primeiro == -1 || f->primeiro > f->ultimo)
        return 1;
    else 
        return 0;
    
}


fila * criar_fila (int tamanho){
    
    fila *f = malloc(sizeof(fila));
    f->itens = malloc(sizeof(int) * tamanho * 10);
    f->primeiro = -1;
    f->ultimo = -1;
    f->tamanho = tamanho*10;
    
    for(int i = 0; i < f->tamanho; i++)
        f->itens[i] = 0;
    
    return f;
    
}


void adicionar (fila *f, int valor){
    
    if(f->ultimo == f->tamanho -1)
        printf("a fila está cheia\n");
    
    else{
        if(f->primeiro == -1)
            f->primeiro = 0;
        f->ultimo++;
        f->itens[f->ultimo] = valor;
    }
}


int remover (fila *f){
    
    int removido;
    
    if(vazio(f)){
        printf("a fila está vazia\n");
        exit(1);
    }
    
    removido = f->itens[f->primeiro];
    f->primeiro++;
    
    return removido;
    
}


void imprimir_fila (fila *f, grafo *g){
    
    int i = f->primeiro;

    if(vazio(f))
        printf("fila vazia\n");
        
    else{
        
        printf("fila: ");
        
        for(i=f->primeiro; i<f->ultimo+1; i++)
            printf("%c ", g->mapa[f->itens[i]]);
        
        printf("\n");
    }
}

//busca

void auxiliar(char vertice, fila *f, grafo *g){
    
    int v = indice(g, vertice);
    
    if(v == -1)
        printf("o vertice não existe\n");
    else
        busca_largura(v, f, g);
}


void busca_largura(int vertice, fila *f, grafo *g){
    
    enum cor cores[g->tamanho];
    int distancia[g->tamanho];
    char predecessor[g->tamanho];
    
    for(int i = 0; i < g->tamanho; i++){
        cores[i] = BRANCO;
        distancia[i] = 999999;
        predecessor[i] = '0';
    }
    
    adicionar(f, vertice);
    
    g->visitado[vertice] = CINZA;
    cores[vertice] = CINZA;
    distancia[vertice] = 0;
    
    printf("O vertice de início será: %c\n", g->mapa[vertice]);
    
    imprimir_fila(f,g);
    
    while(!vazio(f)){
        
        vertice = remover(f);
        
        printf("visitado: %c\n", g->mapa[vertice]);
        
        for(int i = 0; i < g->tamanho; i++){
            if(g->matriz[vertice][i] == 1 && g->visitado[i] == BRANCO){
                adicionar(f,i);
                g->visitado[i] = CINZA;
                cores[i] = CINZA;
                distancia[i] = distancia[vertice]+1;
                predecessor[i] = g->mapa[vertice];
            }
        }
        
        g->visitado[vertice] = PRETO;
        cores[vertice] = PRETO;
        
        imprimir_fila(f,g);
        
    }
    
    printf("\nCORES: ");
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
    
    printf("DISTANCIAS: ");
    for(int i = 0; i < g->tamanho; i++){
        printf("%d ", distancia[i]);
    }
    
    printf("\n");
    
    printf("PREDECESSORES: ");
    for(int i = 0; i < g->tamanho; i++){
        printf("%c ", predecessor[i]);
    }
    
    printf("\n");
    
}
