#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"

grafo * criar_grafo(int tamanho){
    grafo *g = malloc(sizeof(grafo));
    
	g->tamanho = tamanho;
	g->mapa = (char *) malloc(sizeof(char) * tamanho);
	g->matrix = (int **) malloc(sizeof(int *) * tamanho);

    int i,j;
	for(i=0; i < tamanho; i++){
		g->matrix[i] = (int *) malloc(sizeof(int) * tamanho);        
    }

	for(i=0; i < tamanho; i++) {
		for(j=0; j < tamanho; j++) {
            g->matrix[i][j] = 0;
		}
	}
	
    return g;
}


void adicionar_aresta(grafo *g, int v1, int v2, int peso){
    
    g->matrix[v1][v2] = peso;
    g->matrix[v2][v1] = peso;
}


void imprime_Adj_matrix(grafo *g){
    
    int i, j;

    printf("Representação em forma de matriz:\n\n  ");

    for(i=0; i<g->tamanho;i++){
        printf("%c ", g->mapa[i]);
    }
    printf("\n");

    for(i=0; i<g->tamanho; i++) {
        
        printf("%c ", g->mapa[i]);
        
        for (j=0; j<g->tamanho; j++) {
            printf("%d ", g->matrix[i][j]);
        }
        
        printf("\n");
    }
    
    printf("\n");
}


int indice(grafo *g, char c){
    
    int i;
    for(i=0; i<g->tamanho; i++){
        if(c == g->mapa[i]){
            return i;
        }
    }
    
    return -1;
}


grafo * iniciar_grafo(grafo *g){
    
    FILE *input;
    input = fopen("entrada3.txt", "r");

    int vertices, arestas, i, peso;
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
        fscanf(input, " %d", &peso);
        adicionar_aresta(g, indice(g, aresta1), indice(g, aresta2), peso);
    }

    fclose(input);
    return g;
}


//kruskal

void sort(lista_arestas *l){ //ordena a lista de arestas em ordem crescente a partir de seu peso
    
    aresta aux;

    for(int i = 1; i < l->quantidade; i++){
        for(int j = 0; j < l->quantidade-1; j++){
            
            if(l->arestas[j].peso > l->arestas[j+1].peso){
                
                aux = l->arestas[j];
                l->arestas[j] = l->arestas[j+1];
                l->arestas[j+1] = aux;
            }
        }
    }
}


int buscar(int pertence[], int v){
    return (pertence[v]);
}


void aplicar_uniao(grafo *g, int *pertence, int va, int vb){

    for(int i = 0; i<g->tamanho; i++){
        
        if(pertence[i] == vb){
            pertence[i] = va;
        }
    }
}


void imprime(grafo *g, lista_arestas *mst){
    
    int custo;
    custo = 0;

    printf("Arestas: [ ");
    
    for(int i = 0; i < g->tamanho-1; i++){
        printf("%c%c ", mst->arestas[i].u, mst->arestas[i].v);
        custo += mst->arestas[i].peso;
    }
    
    printf("]\n");
    printf("Custo mínimo: %d\n", custo);
}


void kruskal(grafo *g){

    int pertence[g->tamanho]; //cada indice indica um vertice do grafo

    int i, j, v1, v2, va, vb;

    aresta aux;
    lista_arestas *lista = (lista_arestas*)malloc(sizeof(lista_arestas));
    lista_arestas *mst = (lista_arestas*)malloc(sizeof(lista_arestas));
    
    lista->quantidade = 0;
    mst->quantidade = 0;
    
    for(i = 1; i < g->tamanho; i++){ //copia todas as arestas para a lista
        for(j = 0; j < i; j++){
            
            if(g->matrix[i][j] != 0){
                
                aux.peso = g->matrix[i][j];
                aux.u = g->mapa[i];
                aux.v = g->mapa[j];
                lista->arestas[lista->quantidade]=aux;
                lista->quantidade++;
                
            }
        }
    }

    sort(lista); //ordena a lista de arestas

    for(i = 0; i < g->tamanho; i++){
        pertence[i] = i;
    }
    
    for(i = 0; i < lista->quantidade; i++){
        //procura o indice da aresta no mapa do grafo
        v1 = indice(g, lista->arestas[i].u);
        v2 = indice(g, lista->arestas[i].v);

        //onde esta v1 e v2
        va = buscar(pertence, v1);
        vb = buscar(pertence, v2);

        if(va != vb){ //se va e vb nao formorem um ciclo, inclui na mst
            
            mst->arestas[mst->quantidade] = lista->arestas[i];
            mst->quantidade = mst->quantidade + 1;
            aplicar_uniao(g, pertence, va, vb);
            
        }
    }

    imprime(g, mst);
} 
