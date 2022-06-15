#include "bst.h" 
#include <stdlib.h>
#include <stdio.h>


//FUNÇÕES AUXILIARES

int altura (arvore a){
    if(a == NULL)
        return 0;
    else{
        int esq = altura(a->esq);
        int dir = altura(a->dir);
        
        if(esq > dir)
            return esq + 1;
        else 
            return dir + 1;
    }
}

int existe(arvore a, int v){
    
    if(a != NULL){
        if(v > a->valor){
            existe(a->dir,v);
        }
        else if(v < a->valor){
            existe(a->esq,v);
        }
        else if(v == a->valor){ //achou o valor
            return 1;
        }
        else{ //o valor não existe
            return 0;
        }
    }
    
    else{
        return 0; 
    }
}

int menor(arvore a){
    
    if(a != NULL){
       if(a->esq != NULL){
           menor(a->esq);
        } 
        else{ //achou o maior valor
            return a->valor;
        }
    }
    
    else{ //arvore vazia
        return 0;
    }
}


// FUNÇOES DA ARVORE

arvore inserir (arvore a, int v){
    
    //caso base -> arvore vazia
    
    if (a == NULL){
        arvore no = (arvore) malloc(sizeof(no));
        no->valor = v;
        no->esq = NULL;
        no->dir = NULL;
        
        return no;
    }
    
    //inserir em uma subarvore
    
    else {
        if (v < a-> valor){
            a->esq = inserir(a->esq,v);
        }else{
            a->dir = inserir(a->dir,v);
        }
        
        return a;
    }
}


arvore remover (arvore a, int v){
    
    int e;
    
    e = existe(a,v);
    
    //se a arvore nao eh vazia
    
    if(a != NULL){
        
        if(e == 1){
            
        if (v > a->valor){
            a->dir = remover(a->dir,v);
        } 
        
        else if (v < a->valor){
            a->esq = remover(a->esq,v);
        } 
        
        else{ //encontrou o valor :)
            
            // zero filhos
            
            if(a->esq == NULL && a->dir ==NULL){
                free(a);
                return NULL;
            }
            
            //um filho a esquerda
            
            if(a->esq != NULL && a->dir ==NULL){
                arvore esq = a->esq;
                free(a);
                return esq;
            }
            
            //um filho a direita
            
            if(a->esq == NULL && a->dir !=NULL){
                arvore dir = a->dir;
                free(a);
                return dir;
            }
            
            //dois filhos
            
            else{
                arvore aux = a->esq;
                
                while(aux->dir != NULL){
                    aux = aux->dir;
                }
                
                a->valor = aux->valor;
                aux->valor = v;
                a->esq = remover(a->esq,v);
                return a;
            }
            
            }
        }
        
        else{ // valor nao existe
            return NULL;
        }
    }
    
    //caso base -> arvore vazia
    
    else{
        
        return NULL;
        
    }
}


// ORDENAÇAO

void preorder(arvore a){
    
    if (a != NULL){
        printf("[%d]", a->valor);
        preorder(a->esq);
        preorder(a->dir);
    } 
}

void inorder(arvore a){
    
    if (a != NULL){
        inorder(a->esq);
        printf("[%d]", a->valor);
        inorder(a->dir);
    } 
}

void posorder(arvore a){
    
    if (a != NULL){
        posorder(a->esq);
        posorder(a->dir);
        printf("[%d]", a->valor);
    }
}


//EXTRAS

int qntPrimos(arvore a){
    
    if(a != NULL){
        int primos = 0;
        
        int cont = 0;
        for(int i = 1; i <= a->valor; i++){
            if(a->valor % i == 0){
                cont ++;
            }
        }
        
        if(cont == 2){
            primos ++;
        }
        
        cont = 0;
        
        return primos + qntPrimos(a->esq) + qntPrimos(a->dir);;
    }
    
    
    else{
        return 0;
    }
}

void reverso(arvore a){
    
    if(a != NULL){
        reverso(a->dir);
        printf("[%d]", a->valor);
        reverso(a->esq);
    }
}

void caminho(arvore a, int v){
    
    int e;
    
    e = existe(a,v);
    
    if(a != NULL){
       if(e == 1){
            if (v > a->valor){
                printf("[%d]", a->valor);
                caminho(a->dir,v);
            } 
        
            else if (v < a->valor){
                printf("[%d]", a->valor);
                caminho(a->esq,v);
            } 
        
            else{ //achou o valor;
                printf("[%d]\n", v);
            }
        } 
        
        else{ //valor não existe
            printf("\n");
        }
    }
    
    //arvore vazia
    else{
        printf("\n");
    }
}

void sucessor(arvore a, int v){
    
    int e;
    
    e = existe(a, v);
    
    if(a != NULL){
        if(e == 1){
            arvore aux = a;
            arvore maior = NULL;
        
            while(aux != NULL){
                
                if(v == aux->valor){ // achou o valor na arvore
                    
                    if(aux->dir != NULL){ // possui valores a direita
                        int m;
                        m = menor(aux->dir);
                        printf("%d\n", m);
                    }
                    else{
                        
                        if(maior!=NULL){ 
                            printf("%d\n", maior->valor);
                        }
                        
                        else{ // ele eh o maior valor da arvore
                            printf("-1\n");
                        }
                    }
                }
                
                if(v > aux->valor){
                    aux = aux->dir;
                }
                
                else{
                    maior = aux;
                    aux = aux->esq;
                }
            }
        }
        
        else{
            printf("-1\n");
        }
    }
    
    else { //arvore vazia
        printf("\n");
    }
}


