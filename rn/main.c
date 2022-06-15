#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

int main(){
    arvore a;
	int opcao;
    int alturaA;
	inicializar(&a);

	while(1) {
		scanf("%d", &opcao);

		switch(opcao) {
            int valor;
            case 1:
                scanf("%d", &valor);
                adicionar(&a, valor);
                break;
            case 10:
                alturaA = altura(a);
                printf("%d\n",alturaA);
                break;
            case 99:
                    exit(0);
		}
	}
    
} 
