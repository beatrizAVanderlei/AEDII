#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

arvore no_null;

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

void imprimir(arvore raiz) {
	printf("(");
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		imprimir(raiz->esq);
		imprimir(raiz->dir);
	}
	printf(")");
}

void imprimir_elemento(arvore raiz) {
	switch(raiz->cor){
		case PRETO:
			printf("\x1b[30m[%d]\x1b[0m", raiz->dado);
			break;
		case VERMELHO:
			printf("\x1b[31m[%d]\x1b[0m", raiz->dado);
			break;
		case DUPLO_PRETO:
			printf("\x1b[32m[%d]\x1b[0m", raiz->dado);
			break;
	}
}

void inicializar(arvore *raiz) {
    *raiz = NULL;
    no_null = (arvore) malloc(sizeof(struct no_rb));
    no_null->cor = DUPLO_PRETO;
    no_null->dado = 0;
    no_null->esq = NULL;
    no_null->dir = NULL;
}

//FUNÇÕES AUXILIARES

enum cor cor(arvore elemento) { //verificar a cor do nó
	enum cor c;
	if(elemento==NULL)
		c = PRETO;
	else
		c = elemento->cor;
	return c;
}

int eh_raiz(arvore elemento) { //verificar se um nó é raiz
	return (elemento->pai == NULL);
}

int eh_filho_esquerdo(arvore elemento) { //verificar se um elemento é filho esquerdo
	return (elemento->pai != NULL && elemento == elemento->pai->esq);
}

int eh_filho_direito(arvore elemento) {
    return(elemento->pai != NULL && elemento == elemento->pai->dir);
}

arvore tio(arvore elemento) { //encontrar o tio do elemento
	return irmao(elemento->pai);
}

arvore irmao(arvore elemento) { //encontrar o irmão do elemento
	if(eh_filho_esquerdo(elemento))
		return elemento->pai->dir;
	else
		return elemento->pai->esq;
}

int maior_elemento(arvore raiz) {
	if(raiz == NULL)
			return -1;
	if(raiz->dir == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->dir);
}

//ADICIONAR

void adicionar(arvore *raiz, int valor){
    
    arvore aux, pai, add;
    aux = *raiz;
    pai = NULL;
    
    while(aux != NULL){
        pai = aux;
        if(valor > aux->dado)
            aux = aux->dir;
        else
            aux = aux->esq;
    }
    
    add = (arvore) malloc(sizeof(struct no_rb));
    add->dado = valor;
    add->esq = NULL;
    add->dir = NULL;
    add->pai = pai;
    add->cor = VERMELHO;
    
    if(eh_raiz(add))
        *raiz = add;
    
    else{
        if(valor > pai->dado)
            pai->dir = add;
        else
            pai->esq = add;
    }
    
    ajustar(raiz, add);
    
}

//REMOVER 

void remover(arvore *raiz, int valor){
    arvore posicao;
    posicao = *raiz;
    
    while(posicao != NULL){
        if(valor == posicao->dado){
            
            //1 filho direito 
            
            if(posicao->esq == NULL && posicao->dir != NULL){
                posicao->dir->cor = PRETO;
                posicao->dir->pai = posicao->pai;
                
                if(eh_raiz(posicao))
                    *raiz = posicao->dir;
                
                else{
                    if(eh_filho_esquerdo(posicao))
                        posicao->pai->esq = posicao->dir;
                    
                    else
                        posicao->pai->dir = posicao->dir;
                }
                
                break;
            }
            
            //1 filho esquerdo
            
            if(posicao->esq != NULL && posicao->dir == NULL){
                posicao->esq->cor = PRETO;
                posicao->esq->pai = posicao->pai;
                
                if(eh_raiz(posicao))
                    *raiz = posicao->esq;
                
                else{
                    if(eh_filho_esquerdo(posicao))
                        posicao->pai->esq = posicao->esq;
                    else
                        posicao->pai->dir = posicao->esq;
                }
                
                break;
            }
            
            //2 filhos
            
            if(posicao->esq != NULL && posicao->dir != NULL) { 
    			posicao->dado = maior_elemento(posicao->esq);   
	    		remover(&posicao->esq, posicao->dado);
                break;
            }
            
            //Sem filhos
            
            if(posicao->esq == NULL && posicao->dir == NULL){
                
                // o valor é a raiz
                
                if(eh_raiz(posicao)){
                    *raiz = NULL;
                    break;
                }
                
                // o valor é vermelho
                
                if(posicao->cor == VERMELHO){
                    if(eh_filho_esquerdo(posicao))
                        posicao->pai->esq = NULL;
                    else
                        posicao->pai->dir = NULL;
            
                    break;
                }
                
                // o valor é preto
                
                else{
                    no_null->pai = posicao->pai;
                    
                    if(eh_filho_esquerdo(posicao))
                        posicao->pai->esq = no_null;
                    else
                        posicao->pai->dir = no_null;
                    
                    reajustar(raiz, no_null);
                    break;
                }                
            }
        }
        
        if(valor > posicao->dado)
            posicao = posicao->dir;
        else
            posicao = posicao->esq;
    }
}

void reajustar(arvore *raiz, arvore elemento){
    
    //CASO 1
    
    if(eh_raiz(elemento)) {
		elemento->cor = PRETO;
        printf("removeu raiz");
        
        if(elemento == no_null){
            printf("removeu raiz");
            *raiz = NULL;}
		return;
	}
    
    //CASO 2
    
    if(cor(elemento->pai) == PRETO
        && cor(irmao(elemento)) == VERMELHO
        && cor(irmao(elemento)->esq) == PRETO
        && cor(irmao(elemento)->dir) == PRETO)
    {
        if(eh_filho_esquerdo(elemento))
            rotacao_simples_esquerda(raiz, elemento->pai);
        else
            rotacao_simples_direita(raiz, elemento->pai);
        
        elemento->pai->pai->cor = PRETO;
        elemento->pai->cor = VERMELHO;
        
        reajustar(raiz, elemento);
        return;
        
    }
    
    //CASO 3
    
    if(cor(elemento->pai) == PRETO
        && cor(irmao(elemento)) == PRETO
        && cor(irmao(elemento)->esq) == PRETO
        && cor(irmao(elemento)->dir) == PRETO)
    {
        elemento->pai->cor = DUPLO_PRETO;
        irmao(elemento)->cor = VERMELHO;
        retira_duplo_preto(raiz, elemento);
        reajustar(raiz, elemento->pai);

        return;
    }
    
    //CASO 4
    
    if(cor(elemento->pai) == VERMELHO
        && cor(irmao(elemento)) == PRETO
        && cor(irmao(elemento)->esq) == PRETO
        && cor(irmao(elemento)->dir) == PRETO)
    {
        elemento->pai->cor = PRETO;
        irmao(elemento)->cor = VERMELHO;
        retira_duplo_preto(raiz, elemento);
        return;
    }
    
    //CASO 5
    
    if(eh_filho_esquerdo(elemento)){
        if(cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->esq) == VERMELHO && cor(irmao(elemento)->dir) == PRETO){
            irmao(elemento)->cor = PRETO;
            irmao(elemento)->dir->cor = VERMELHO;
		
	    rotacao_simples_direita(raiz, irmao(elemento));
            
            reajustar(raiz, elemento);
            return;
        }
    }
    
    if(eh_filho_direito(elemento)){
        if(cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->dir) == VERMELHO && cor(irmao(elemento)->esq) == PRETO){
	    irmao(elemento)->cor = PRETO;
            irmao(elemento)->esq->cor = VERMELHO;
		
            rotacao_simples_esquerda(raiz, irmao(elemento));
            
            reajustar(raiz, elemento);
            return;
        }
    }
    
    //CASO 6
    
    if(eh_filho_esquerdo(elemento)){
        if(cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->dir) == VERMELHO){
            irmao(elemento)->cor = elemento->pai->cor;
            rotacao_simples_esquerda(raiz, elemento->pai);
            
            elemento->pai->cor = PRETO;
            irmao(elemento->pai)->cor = PRETO;
            
            retira_duplo_preto(raiz, elemento);
            return;          
        }
    }
    
    if(eh_filho_direito(elemento)){
        if(cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->esq) == VERMELHO){
            irmao(elemento)->cor = elemento->pai->cor;
            rotacao_simples_direita(raiz, elemento->pai);
            
            elemento->pai->cor = PRETO;
            irmao(elemento->pai)->cor = PRETO;
            
            retira_duplo_preto(raiz, elemento);
            return;
        }
    }
}

void retira_duplo_preto(arvore *raiz, arvore elemento) {
			if(elemento == no_null)
				if(eh_filho_esquerdo(elemento))
						elemento->pai->esq = NULL;
				else
						elemento->pai->dir = NULL;
			else
				elemento->cor = PRETO;
}

//AJUSTES

void ajustar(arvore *raiz, arvore elemento){
    
    while(cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO){
        
        //CASO 1:
        
        if(cor(tio(elemento)) == VERMELHO){
            tio(elemento) -> cor = PRETO;
            elemento->pai->cor = PRETO;
            elemento->pai->pai->cor = VERMELHO;
            elemento = elemento->pai->pai;
            
            continue;
        }
        
        //CASO 2 - DIREITA:
        
        if(eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)){
            rotacao_simples_direita(raiz, elemento->pai->pai);
            elemento->pai->cor = PRETO;
            elemento->pai->dir->cor = VERMELHO;
            
            continue;
        }
        
        //CASO 2 - ESQUERDA:
        
        if(eh_filho_direito(elemento) && eh_filho_direito(elemento->pai)){
            rotacao_simples_esquerda(raiz, elemento->pai->pai);
            elemento->pai->cor = PRETO;
            elemento->pai->esq->cor = VERMELHO;
            
            continue;
        }
        
        //CASO 3 - DIREITA
        
        if(eh_filho_direito(elemento) && eh_filho_esquerdo(elemento->pai)){
            rotacao_dupla_direita(raiz, elemento->pai->pai);
            elemento->dir->cor = VERMELHO;
            elemento->esq->cor = VERMELHO;
            elemento->cor = PRETO;
            
            continue;
        }
        
        //CASO 3 - ESQUERDA
        
        if(eh_filho_esquerdo(elemento) && eh_filho_direito(elemento->pai)){
            rotacao_dupla_esquerda(raiz, elemento->pai->pai);
            elemento->dir->cor = VERMELHO;
            elemento->esq->cor = VERMELHO;
            elemento->cor = PRETO;
            
            continue;
        }
        
    }
    
    (*raiz)->cor = PRETO;
}

//ROTAÇÕES

/*     p             u
      / \           / \
     u  t2   =>    v   p
    / \               / \
   v  t1             t1 t2

*/

void rotacao_simples_direita(arvore *raiz, arvore pivo){
    arvore u, t1;
    u = pivo->esq;
    t1 = u->dir;
    
    int posicao_pivo_esq = eh_filho_esquerdo(pivo);
    
    pivo->esq = t1;
    
    if(t1 != NULL)
        t1->pai = pivo;
    
    u->dir = pivo;
    u->pai = pivo->pai;
    pivo->pai = u;
    
    if(eh_raiz(u))
        *raiz = u;
    
    else{
        if(posicao_pivo_esq)
            u->pai->esq = u;
        else
            u->pai->dir = u;
    }
    
}

void rotacao_simples_esquerda(arvore *raiz, arvore pivo){
    arvore u, t1;
    u = pivo->dir;
    t1 = u->esq;
    
    int posicao_pivo_dir = eh_filho_direito(pivo);
    
    pivo->dir = t1;
    
    if(t1 != NULL)
        t1->pai = pivo;
    
    u->esq = pivo;
    u->pai = pivo->pai;
    pivo->pai = u;
    
    if(eh_raiz(u))
        *raiz = u;
    
    else{
        if(posicao_pivo_dir)
            u->pai->dir = u;
        else
            u->pai->esq = u;
    }
}

 /*   p               p               v
     / \             / \             / \
    u  t4     =>    v   t4    =>    u    p
   / \             / \             / \  / \
  t1  v           u  t3           t1 t2 t3 t4
     / \         / \
    t2  t3      t1  t2

 */

void rotacao_dupla_direita(arvore *raiz, arvore pivo){
    arvore v, p, u, t2, t3;
    p = pivo;
    u = p->esq;
    v = u->dir;
    t2 = v->esq;
    t3 = v->dir;
    
    int posicao_pivo_esq = eh_filho_esquerdo(pivo);
    
    u->dir = t2;
    
    if(t2 != NULL)
        t2->pai = u;
    
    v->esq = u;
    p->esq = v;
    p->esq = t3;
    
    if(t3 != NULL)
        t3->pai = p;
    
    v->dir = p;
    v->pai = p->pai;
    p->pai = v;
    u->pai = v;
    
    if(eh_raiz(v))
        *raiz = v;
    
    else{
        if(posicao_pivo_esq)
            v->pai->esq = v;
        else
            v->pai->dir = v;
    }
}

 /*   p               p               v
     / \             / \             / \
    t1  u     =>    t1  v    =>     p    u
       / \             / \         / \  / \
      v  t4           t2  u       t1 t2 t3 t4
     / \                 / \
    t2  t3              t3  t4

 */

void rotacao_dupla_esquerda(arvore *raiz, arvore pivo){
    arvore v, p, u, t2, t3;
    p = pivo;
    u = p -> dir;
    v = u -> esq;
    t2 = v -> esq;
    t3 = v -> dir;
    
    int posicao_pivo_dir = eh_filho_direito(p);
    
    u->esq = t3;
    
    if(t3 != NULL)
        t3->pai = u;
    
    v->dir = u;
    p->dir = v;
    p->dir = t2;
    
    if(t2 != NULL)
        t2->pai = p;
    
    v->esq = p;
    v->pai = p->pai;
    p->pai = v;
    u->pai = v;
    
    if(eh_raiz(v))
        *raiz = v;
    
    else{
        if(posicao_pivo_dir)
            v->pai->dir = v;
        else
            v->pai->esq = v;
    }
}
