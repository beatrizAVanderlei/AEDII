#include <stdio.h>
#include <stdlib.h>
#include "profundidade.h" 

int main(){
    
    grafo *g;
    
    g = iniciar_grafo(g);
    
    imprime_grafo(g);
    
    DFS(g);
    
    return 0;  
}
