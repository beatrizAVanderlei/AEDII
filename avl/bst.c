#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

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

void incializar(arvore *a){
    *a = NULL;
}

arvore inserir(arvore a, int v, int *cresceu){
    
    if(a == NULL){ //caso base de nó vazio
        arvore novo = (arvore) malloc(sizeof(no_avl));
        novo->raiz = v;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->fator = 0;
        * cresceu = 1; 
        return novo;
    }
    
    if(v > a->raiz){ //o elemento vai ser adicionado a direita
        a->dir = inserir(a->dir, v, cresceu);
        
        if(*cresceu){ //calcular os reajustes dos fatores de balanço
            switch(a->fator){
                case 0:
                    // a arvore estava balanceada e cresceu um ponto para a direita
                    a->fator = 1;
                    *cresceu = 1;
                    break;
                case -1:
                    // a arvore estava pendendo um ponto para a esquerda e ficou balanceada
                    a->fator = 0;
                    *cresceu = 0;
                    break;
                case 1:
                    // a arvore estava pendendo um ponto para a direita e agora irá pender 2, logo, terá de ser rotacionada
                    *cresceu = 0;
                    return rotacionar(a);
            }
        }
    }
    
    else{ //o elemento vai ser adicionado a esquerda
        a->esq = inserir(a->esq, v, cresceu);
        
        if(*cresceu){ //calcular os reajustes dos fatores de balanço
            switch(a->fator){
                case 0:
                    // a arvore estava balanceada e cresceu um ponto para a esquerda
                    a->fator = -1;
                    *cresceu = 1;
                    break;
                case 1:
                    // a arvore estava pendendo um ponto para a direita e ficou balanceada
                    a-> fator = 0;
                    *cresceu = 0;
                    break;
                case -1:
                    // a arvore estava pendendo um ponto para a esquerda e agora irá pender 2, logo, terá de ser rotacionada
                    *cresceu = 0;
                    return rotacionar(a);
                
            }
        }
        
    }
    
    return a;
    
}


arvore remover(arvore a, int v, int *diminuiu){
    
    
    if(a == NULL){
        *diminuiu = 0;
        return NULL;
    }
    
    else{ //caso base que a árvore não é vazia
        
        if(v == a->raiz){ //encontrou o valor
            *diminuiu = 1;
            
            if(a->esq == NULL && a->dir == NULL){ //não tem filhos
                free(a);
                return NULL;                
            }
            
            if(a->esq == NULL && a->dir != NULL){ //tem um filho a direita
                arvore dir = a->dir;
                free(a);
                return dir;
            }
            
            if(a->esq != NULL && a->dir == NULL){ //tem um filho a esquerda
                arvore esq = a->esq;
                free(a);
                return esq;
            }
            
            else{ //tem dois filhos
                arvore aux = a->esq;
                
                while(aux->dir != NULL){
                    aux = aux->dir;
                }
                
                a->raiz = aux->raiz;
                aux->raiz = v;
                a->esq = remover(a->esq, v, diminuiu);
                
                if(*diminuiu){
                    switch(a->fator){
                        case 0:
                            a->fator = 1;
                            *diminuiu = 0;
                            break;
                        case -1:
                            a->fator = 0;
                            *diminuiu = 1;
                            break;
                        case 1:
                            *diminuiu = 1;
                            return rotacionar(a);
                    }
                }
                
                return a;                
            }
            
        }
       
        if(v > a->raiz){
            a->dir = remover(a->dir, v, diminuiu);
           
            if(*diminuiu){ //remover um numero a direita
                switch(a->fator){
                    case 0: //a arvore estava balanceada e diminuiu um ponto para a direita
                        a->fator = -1;
                        *diminuiu = 0;
                        break;
                    case 1: // a arvore estava pendendo um ponto para a direita e ficou balanceada
                        a->fator = 0;
                        *diminuiu = 1;
                        break;
                    case -1: // a arvore estava pendendo um ponto para a esquerda e agora irá pender dois
                        *diminuiu = 1;
                        return rotacionar(a);
                }
               
            }
        }
        
        else{
            a->esq = remover(a->esq, v, diminuiu);
            
            if(*diminuiu){
                switch(a->fator){
                    case 0: // a arvore estava balanceada e diminuiu um ponto para a esquerda
                        a->fator = 1;
                        *diminuiu = 0;
                        break;
                    case -1: // a arvore estava pendendo um ponto para a esquerda e ficou balanceada
                        a->fator = 0;
                        *diminuiu = 1;
                        break;
                    case 1: // a arvore estava pendendo um ponto para a direita e agora irá pender dois
                        *diminuiu = 1;
                        return rotacionar(a);
                }
            }
        }
        
        return a;
    }
}


// ROTAÇÕES


arvore rotacionar(arvore a){ //fazer todas as chamadas de processo de rotação
    
    if(a->fator > 0){ //rotações p esquerda
        switch(a->dir->fator){
            arvore p; //raiz da rotação
            case 0:
                
            case 1:
                p = simples_esquerda(a);
                return p;
            case -1:
                return dupla_esquerda(a);
        }
    }
    
    else{ //rotações p direita
        switch(a->esq->fator){
            arvore p; //raiz da rotação
            case 0:
                
            case -1:
                p = simples_direita(a);
                return p;
            case 1:
                return dupla_direita(a);
                
        }
        
    }
} 

 /*   p              u
     / \            / \
    u  t3     =>   t1  p 
   / \                / \
  t1 t2              t2 t3

 */

arvore simples_direita(arvore a){
    arvore p, u;
    p = a;
    u = a->esq;
    
    //rotação
    
    p->esq = u->dir;
    u->dir = p;
    
    //fatores de balanço
    
    if(u->fator == -1){
        p->fator = 0;
        u->fator = 0;
    }
    
    else{
        p->fator = -1;
        u->fator = 1;
    }
    
    return u;
}


 /*   p              u
     / \            / \
    t1  u     =>   p   t3 
       / \        / \
      t2 t3      t1 t2

 */
 
arvore simples_esquerda(arvore a){
    arvore p, u, t1, t2, t3;
    p = a;
    u = a->dir;
    
    
    //rotação
    
    p->dir = u->esq;;
    u->esq = p;
    
    // atualização dos fatores de balanço;
    
    if(u->fator == 1){
        p->fator = 0;
        u->fator = 0;
    } 
    
    else{
        p->fator = 1;
        u->fator = -1;
    }
    
    return u;
}

 /*   p               p               v
     / \             / \             / \
    u  t4     =>    v   t4    =>    u    p
   / \             / \             / \  / \
  t1  v           u  t3           t1 t2 t3 t4
     / \         / \
    t2  t3      t1  t2

 */

arvore dupla_direita(arvore a){
    arvore p, u, v;
    p = a;
    u = a->esq;
    v = u->dir;
    
    //rotação
    
    u->dir = v->esq;
    v->esq = u;
    
    p->esq = v->dir;
    v->dir = p;
    
    //fatores de balanço
    
    switch(v->fator){
        case -1:
            p->fator = 1;
            u->fator = 0;
            v->fator = 0;
            break;
        case 1:
            p->fator = 0;
            u->fator = -1;
            v->fator = 0;
            break;
        case 0:
            p->fator = 0;
            u->fator = 0;
            v->fator = 0;
            break;
    }
    
    return v;
    
}

 /*   p               p               v
     / \             / \             / \
    t1  u     =>    t1  v    =>     p    u
       / \             / \         / \  / \
      v  t4           t2  u       t1 t2 t3 t4
     / \                 / \
    t2  t3              t3  t4

 */
 
arvore dupla_esquerda(arvore a){
    arvore p, u, v;
    p = a;
    u = a->dir;
    v = u->esq;
    
    //rotações
    
    u->esq = v->dir;
    v->dir = u;
    
    p->dir = v->esq;
    v->esq = p;
    
    //fatores de balanço
    
    switch(v->fator){
        case -1:
            p->fator = 0;
            u->fator = 1;
            v->fator = 0;
            break;
        case 1:
            p->fator = -1;
            u->fator = 0;
            v->fator = 0;
            break;
        case 0:
            p->fator = 0;
            u->fator = 0;
            v->fator = 0;
            break;
    }
    
    return v;
}


// IMPRIMIR

void imprimir(arvore a) {
    printf("(");
    if(a != NULL) {
        imprimir_elemento(a);
        imprimir(a->esq);
        imprimir(a->dir);
    }
    printf(")");
}

void imprimir_elemento(arvore a) {
    printf("%d [%d]", a->raiz, a->fator);
}
 
