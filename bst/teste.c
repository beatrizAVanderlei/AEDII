#include "bst.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    
    arvore a; //arvore
    int valor;
    int opcao; //case do switch
    int alturaA;
    
    int pri; //variavel auxiliar p quantidade de primos
    
    //inicializar a arvore
    
    a = NULL;
    
    while(1){
        
        scanf("%d", &opcao);
        
        switch(opcao){
            
            case 1: //inserir
                
                scanf("%d", &valor);
                a = inserir(a,valor);
                break;
            
            case 10: //altura
                
                alturaA = altura(a);
                printf("%d\n", alturaA);
                break;
            
            case 99: //saida
                
                exit(0);
            
        }
    }
    
}
