#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


int main(){
    arvore a;
	int opcao;
	int controleFB;
    int alturaA;
	incializar(&a);

	while(1) {
		scanf("%d", &opcao);

		switch(opcao) {
				int valor;
				case 1:
                    scanf("%d", &valor);
                    a = inserir(a, valor, &controleFB);
                    break;
                case 10:
                    alturaA = altura(a);
                    printf("%d\n", alturaA);
                    break;
				case 99:
						exit(0);
		}
	}
    
}
