#include <stdio.h>
#include <stdlib.h>
#include "largura.h"

int main(){
    
    grafo *g;
    fila *f;
    char vertice_inicial;

    g = iniciar_grafo(g);
    f = criar_fila(g->tamanho);
    
    printf("Insira o vértice de início: \n");
    
    scanf("%c", &vertice_inicial); 
    
    printf("\n");
        
    auxiliar(vertice_inicial, f, g);
    
    printf("\nRepresentação matriarcal\n");
    
    imprime_matriz(g);
    
    return 0;
}
 
